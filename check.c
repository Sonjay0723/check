#include<stdio.h>
#include<stdlib.h>

typedef struct node {
  char *ptr;
  struct node *next;
}node;

node *newNode(char *item) {
  struct node *root = (node*)malloc(sizeof(node));
  root->ptr = item;
  root->next = NULL;
  return root;
}

void insertNode(struct node *head, char *item) {
  struct node *tail = newNode(item);
  struct node *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = tail;
}

void printList(struct node *head){
  if (head == NULL) {
    return;
  }
  struct node *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->ptr);
        temp = temp->next;
    }
}

char *mystrtok(char* string, const char *delim)
{
  char *str;
  static char *ptr;
  const char *del;
  if(string != NULL)
  {
    ptr = string;
    str = string;
  }
  else
  {
      if(*ptr == '\0') {
        return NULL;
      }
      else {
        str = ptr;
      }
  }

  while(*ptr != '\0') {
    del = delim;

    while(*del != '\0') {
      if(*ptr == *del) {
        if(ptr == str) {
          ptr++;
          str++;
        }
        else {
          *ptr = '\0';
          ptr++;
          return str;
        }
      }
      else {
        del++;
      }
    }
    
    ptr++;
  }

  return str;
}

void semicolonSeperate(struct node *head) {
  struct node *temp = newNode(";");
  char *str = head->ptr;
  int i = 0;

  while (str[i] != ';' && str[i] != '\0') {
    i++;
  }

  if (str[i] == ';') {
    str[i] = '\0';

    temp->next = head->next;
    head->next = temp;
  }
}

int stringCompare(char *str1, char *str2) {
  if (str1[0] == '\0' && str2[0] == '\0') {
    return 0;
  }

  int i = 0;

  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return 1;
    }
    i++;
  }

  if (str1[i] != '\0' || str2[i] != '\0') {
    return 1;
  }

  return 0;
}

void printError(int expression, char *errorType, char *error, char *str) {
  printf("Error: %s error in expression %d: %s\n\t\"%s\"\n", errorType, expression, error, str);
}

void printArith(int expNum, struct node *head) {
  if (head == NULL) {
    printError(expNum, "Scan", "incomplete expression", "");
    return;
  }
  char *arithOperators[] = {"+", "-", "*", "/"};
  char *logicOperators[] = {"AND", "OR", "NOT"};
  char *arithOperands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  char *logicOperands[] = {"true", "false"};
  int arithOperatorsNum = 4;
  int logicOperatorsNum = 3;
  int arithOperandsNum = 10;
  int logicOperandsNum = 2;

  int i = 0;
  int operand1 = 0;
  int operand2 = 0;
  int operator = 0;
  char *tempStr = "";
  char *operatorStr = "";
  /*
  Key:
  0 = unexpected/empty
  1 = found
  2 = already counted
  */
  struct node *temp = head;
  while (temp != NULL) {
    if (operand1 == 0 && operator == 0) {
      for (i = 0; i < arithOperandsNum; i++) {
        if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
          operand1 = 1;
          break;
        }
      }
    }

    if (operator == 0) {
      for (i = 0; i < arithOperatorsNum; i++) {
        if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
          operator = 1;
          operatorStr = temp->ptr;
          break;
        }
      }

      if (operator == 1) {
        temp = temp->next;
        operator = 2;
        continue;
      }
    }

    if (operand2 == 0 && operator > 0) {
      for (i = 0; i < arithOperandsNum; i++) {
        if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
          operand2 = 1;
          break;
        }
      }
    }

    if (operator == 0) {
      if (operand1 != 1) {
        if (stringCompare(temp->ptr, "") == 0){
          printError(expNum, "Scan", "incomplete expression", temp->ptr);
        }
        else {
          if (operand1 == 0) {
            tempStr = "unknown identifier";
          }
          else {
            tempStr = "unknown operator";
          }

          for (i = 0; i < arithOperatorsNum; i++) {
            if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < arithOperandsNum; i++) {
            if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
              tempStr = "unexpected operand";
              break;
            }
          }
          for (i = 0; i < logicOperatorsNum; i++) {
            if (stringCompare(logicOperators[i], temp->ptr) == 0) {
              tempStr = "operator type mismatch";
              break;
            }
          }
          for (i = 0; i < logicOperandsNum; i++) {
            if (stringCompare(logicOperands[i], temp->ptr) == 0) {
              tempStr = "operand type mismatch";
              operand1 = 2;
              break;
            }
          }

          printError(expNum, "Parse", tempStr, temp->ptr);
        }
      }
      else {
        operand1 = 2;
      }
    } //operator == 0
    else {
      if (operand1 == 0 && operator > 0) {
        printError(expNum, "Parse", "unexpected operator", operatorStr);
        operand1 = 2;
      }

      if (operand2 == 2) {
        printError(expNum, "Parse", "expression wasn't ended", temp->ptr);
        operand2 = 3;
      }

      if (operand2 < 1) {
        if (stringCompare(temp->ptr, "") == 0){
          printError(expNum, "Scan", "incomplete expression", temp->ptr);
        }
        else {
          tempStr = "unknown operand";

          for (i = 0; i < arithOperatorsNum; i++) {
            if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < logicOperatorsNum; i++) {
            if (stringCompare(logicOperators[i], temp->ptr) == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < logicOperandsNum; i++) {
            if (stringCompare(logicOperands[i], temp->ptr) == 0) {
              tempStr = "operand type mismatch";
              operand2 = 2;
              break;
            }
          }

          printError(expNum, "Parse", tempStr, temp->ptr);
          operand2 = 2;
        }
      }
      else if (operand2 > 1) {
        tempStr = "unknown operand";

        for (i = 0; i < arithOperatorsNum; i++) {
          if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
            tempStr = "unexpected operator";
            break;
          }
        }
        for (i = 0; i < arithOperandsNum; i++) {
          if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
            tempStr = "unexpected operand";
            break;
          }
        }
        for (i = 0; i < logicOperatorsNum; i++) {
          if (stringCompare(logicOperators[i], temp->ptr) == 0) {
            tempStr = "unexpected operator";
            break;
          }
        }
        for (i = 0; i < logicOperandsNum; i++) {
          if (stringCompare(logicOperands[i], temp->ptr) == 0) {
            tempStr = "unexpected operand";
            break;
          }
        }

        printError(expNum, "Parse", tempStr, temp->ptr);
      }
      else {
        operand2 = 2;
      }

      operator = 2;
    } //operator == 1
    temp = temp->next;
  } //end of while

  if (operand2 == 0 && operator > 0) {
    printError(expNum, "Scan", "missing operand", "");
    operand2 = 2;
  }
}

void printLogic(int expNum, struct node *head) {
  if (head == NULL) {
    printError(expNum, "Scan", "incomplete expression", "");
    return;
  }
  char *arithOperators[] = {"+", "-", "*", "/"};
  char *arithOperands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  //char *logicOperators[] = {"AND", "OR", "NOT"};
  char *logicOperators[] = {"AND", "OR"};//, "NOT"};
  char *logicOperands[] = {"true", "false"};
  int arithOperatorsNum = 4;
  //int logicOperatorsNum = 3;
  int logicOperatorsNum = 2;
  int arithOperandsNum = 10;
  int logicOperandsNum = 2;

  int i = 0;
  int not1 = 0;
  int not2 = 0;
  int operand1 = 0;
  int operand2 = 0;
  int operator = 0;
  char *tempStr = "";
  char *operatorStr = "";
  /*
  Key:
  0 = unexpected/empty
  1 = found
  2 = already counted
  */
  struct node *temp = head;
  while (temp != NULL) {
    if (operand1 == 0 && operator == 0) {
      if (stringCompare(temp->ptr, "NOT") == 0 && not1 == 0) {
        not1 = 1;
        temp = temp->next;
        continue;
      }

      for (i = 0; i < logicOperandsNum; i++) {
        if (stringCompare(temp->ptr, logicOperands[i]) == 0) {
          operand1 = 1;
          not1 = 2;
          break;
        }
      }
    }

    if (operator == 0) {
      for (i = 0; i < logicOperatorsNum; i++) {
        if (stringCompare(logicOperators[i], temp->ptr) == 0) {
          operator = 1;
          not1 = 2;
          operatorStr = temp->ptr;
          break;
        }
      }

      if (operator == 1) {
        temp = temp->next;
        operator = 2;
        continue;
      }
    }

    if (operand2 == 0 && operator > 0) {
      if (stringCompare(temp->ptr, "NOT") == 0 && not2 == 0) {
        not2 = 1;
        temp = temp->next;
        continue;
      }

      for (i = 0; i < logicOperandsNum; i++) {
        if (stringCompare(temp->ptr, logicOperands[i]) == 0) {
          operand2 = 1;
          not2 = 2;
          break;
        }
      }
    }

    if (operator == 0) {
      if (operand1 != 1) {
        if (stringCompare(temp->ptr, "") == 0){
          printError(expNum, "Scan", "incomplete expression", temp->ptr);
        }
        else {
          if (operand1 == 0) {
            tempStr = "unknown identifier";
          }
          else {
            tempStr = "unknown operator";
          }

          for (i = 0; i < logicOperatorsNum; i++) {
            if (stringCompare(logicOperators[i], temp->ptr) == 0 || stringCompare(temp->ptr, "NOT") == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < logicOperandsNum; i++) {
            if (stringCompare(logicOperands[i], temp->ptr) == 0) {
              tempStr = "unexpected operand";
              break;
            }
          }
          for (i = 0; i < arithOperatorsNum; i++) {
            if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
              tempStr = "operator type mismatch";
              break;
            }
          }
          for (i = 0; i < arithOperandsNum; i++) {
            if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
              tempStr = "operand type mismatch";
              operand1 = 2;
              break;
            }
          }

          printError(expNum, "Parse", tempStr, temp->ptr);
        }
      }
      else {
        operand1 = 2;
      }
    } //operator == 0
    else {
      if (operand1 == 0 && operator > 0) {
        printError(expNum, "Parse", "unexpected operator", operatorStr);
        operand1 = 2;
      }

      if (operand2 == 2) {
        printError(expNum, "Parse", "expression wasn't ended", temp->ptr);
        operand2 = 3;
      }

      if (operand2 < 1) {
        if (stringCompare(temp->ptr, "") == 0){
          printError(expNum, "Scan", "incomplete expression", temp->ptr);
        }
        else {
          tempStr = "unknown operand";

          for (i = 0; i < arithOperatorsNum; i++) {
            if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < logicOperatorsNum; i++) {
            if (stringCompare(logicOperators[i], temp->ptr) == 0 || stringCompare(temp->ptr, "NOT") == 0) {
              tempStr = "unexpected operator";
              break;
            }
          }
          for (i = 0; i < arithOperandsNum; i++) {
            if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
              tempStr = "operand type mismatch";
              operand2 = 2;
              break;
            }
          }

          printError(expNum, "Parse", tempStr, temp->ptr);
          operand2 = 2;
        }
      }
      else if (operand2 > 1) {
        tempStr = "unknown operand";

        for (i = 0; i < arithOperatorsNum; i++) {
          if (stringCompare(temp->ptr, arithOperators[i]) == 0) {
            tempStr = "unexpected operator";
            break;
          }
        }
        for (i = 0; i < arithOperandsNum; i++) {
          if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
            tempStr = "unexpected operand";
            break;
          }
        }
        for (i = 0; i < logicOperatorsNum; i++) {
          if (stringCompare(logicOperators[i], temp->ptr) == 0 || stringCompare(temp->ptr, "NOT") == 0) {
            tempStr = "unexpected operator";
            break;
          }
        }
        for (i = 0; i < logicOperandsNum; i++) {
          if (stringCompare(logicOperands[i], temp->ptr) == 0) {
            tempStr = "unexpected operand";
            break;
          }
        }

        printError(expNum, "Parse", tempStr, temp->ptr);
      }
      else {
        operand2 = 2;
      }

      operator = 2;
    } //operator == 1
    temp = temp->next;
  } //end of while

  if (operand2 == 0 && operator > 0) {
    printError(expNum, "Scan", "missing operand", "");
    operand2 = 2;
  }
  else if (operator == 0) {
    printError(expNum, "Scan", "missing operator", "");
  }
}

void printUnknown(int expNum, struct node *head){
  if (head == NULL || stringCompare(head->ptr, "") == 0) {
    printError(expNum, "Scan", "incomplete expression", "");
    return;
  }
  char *arithOperators[] = {"+", "-", "*", "/"};
  char *arithOperands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  char *logicOperators[] = {"AND", "OR", "NOT"};
  char *logicOperands[] = {"true", "false"};
  int arithOperatorsNum = 4;
  int logicOperatorsNum = 3;
  int arithOperandsNum = 10;
  int logicOperandsNum = 2;

  int i = 0;
  int not1 = 0;
  int not2 = 0;
  int type = 0; //1 is arithmetic, 2 is logical
  int operand1 = 0;
  int operand2 = 0;
  int operator = 0;
  char *tempStr = "";
  char *operatorStr = "";
  /*
  Key:
  0 = unexpected/empty
  1 = found
  2 = already counted
  */
  struct node *temp = head;
  while (type == 0) { //check what type of expression this is
    for (i = 0; i < arithOperandsNum; i++) {
      if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
        type = 1;
        operand1 = 1;
        break;
      }
    }

    for (i = 0; i < logicOperandsNum; i++) {
      if (stringCompare(temp->ptr, logicOperands[i]) == 0) {
        type = 2;
        operand1 = 1;
        break;
      }
    }

    if (type == 0) {
      printError(expNum, "Parse", "unknown identifier", temp->ptr);
    }
    temp = temp->next;
  } //end of while type == 0

  while (temp != NULL) {
    if (operand2 == 0) {
      for (i = 0; i < arithOperandsNum; i++) {
        if (stringCompare(temp->ptr, arithOperands[i]) == 0) {
          operand2 = 1;
          if (type == 2) {
            printError(expNum, "Parse", "operand type mismatch", temp->ptr);
          }
          if (operator == 0) {
            printError(expNum, "Scan", "missing operator", temp->ptr);
            operator = 1;
          }
        }
      }

      for (i = 0; i < logicOperandsNum; i++) {
        if (stringCompare(temp->ptr, logicOperands[i]) == 0) {
          operand2 = 1;
          if (type == 1) {
            printError(expNum, "Parse", "operand type mismatch", temp->ptr);
          }
          if (operator == 0) {
            printError(expNum, "Scan", "missing operator", temp->ptr);
            operator = 1;
          }
        }
      }

      if (operator == 0) {
        printError(expNum, "Parse", "unexpected operator", temp->ptr);
        operator = 1;
      }
    } //end if operand2 == 0
    else {
      if (operand2 == 1) {
        printError(expNum, "Parse", "expression wasn't ended", temp->ptr);
        operand2 = 2;
      }

      printError(expNum, "Parse", "unexpected operand", temp->ptr);
    } //end if operand2 != 0

    temp = temp->next;
  }

  if (operand1 == 0) {
    printError(expNum, "Scan", "missing operand", "");
  }
  else if (operator == 0) {
    printError(expNum, "Scan", "missing operator", "");
  }
  else if (operand2 == 0) {
    printError(expNum, "Scan", "missing operand", "");
  }
}

int main(int argc, char **argv) {
  int expressions = 1;
  int logicals = 0;
  int arithmetics = 0;
  int i, j;

  int argsLength = 0;
  while (argv[1][argsLength] != '\0') {
    argsLength++;
  }

  for (i = 0; i < argsLength; i++) {
    if (argv[1][i] == ';')
      expressions++;
  }

  j = 0;
  struct node *head = newNode("");
  char *ogString = argv[1];
  for (i = 0; ; i++, ogString = NULL) {
    char *str = mystrtok(ogString, " ");
    if (str == NULL) {
      break;
    }
    //printf("%d: %s\n", i, str);
    insertNode(head, str);
  }
  if (argsLength > 0) {
    head = head->next;
  }
  //printList(head);

  struct node *temp = head;
  int changed = 0;
  while (temp != NULL) {
    char *tempStr = temp->ptr;
    i = 0;
    changed = 0;
    while (tempStr[i] != '\0') {
      if (tempStr[i] == ';') {
        semicolonSeperate(temp);
        if (temp->next != NULL) {
          temp = temp->next->next;
          changed = 1;
        }
        continue;
      }
      i++;
    }
    if (changed == 0) {
      temp = temp->next;
    }
  }

  //printList(head);

  char *arithOperators[] = {"+", "-", "*", "/"};
  char *arithOperands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  char *logicOperators[] = {"AND", "OR", "NOT"};
  char *logicOperands[] = {"true", "false"};
  int arithOperatorsNum = 4;
  int logicOperatorsNum = 3;
  int arithOperandsNum = 10;
  int logicOperandsNum = 2;

  struct node *expArray[expressions];
  for (i = 0; i < expressions; i++) {
    expArray[i] = NULL;
  }

  if (head->ptr[0] == ';') {
    expArray[1] = head;
    i = 1;
  }
  else {
    expArray[0] = head;
    i = 0;
  }

  temp = head;
  j = 0;
  int k;
  while (temp->next != NULL) {
    if (temp->next->ptr[0] == ';') {
      i++;
      if (temp->next->next != NULL) {
        expArray[i] = temp->next->next;
        temp->next = NULL;
        temp = expArray[i];
      }
      else {
        temp->next = NULL;
      }
    }
    else {
      temp = temp->next;
    }
  }

  /*for (i = 0; i < expressions; i++) {
    printList(expArray[i]);
    printf("----\n");
  }*/

  int expValues[expressions];
  for (i = 0; i < expressions; i++) {
    expValues[i] = 0;
  }

  /*
  Key:
  0 = missing
  1 = arithmetic
  2 = logical
  */
  for (i = 0; i < expressions; i++) {
    temp = expArray[i];
    while (temp != NULL) {
      char *tempStr = temp->ptr;

      for (j = 0; j < arithOperatorsNum; j++) {
        if (stringCompare(tempStr, arithOperators[j]) == 0 && expValues[i] == 0) {
          expValues[i] = 1;
        }
      }

      for (j = 0; j < logicOperatorsNum; j++) {
        if (stringCompare(tempStr, logicOperators[j]) == 0 && expValues[i] == 0) {
          expValues[i] = 2;
        }
      }

      temp = temp->next;
    }
  }

  for (i = 0; i < expressions; i++) {
    //printf("type: %d\n", expValues[i]);
    if (expValues[i] == 1) {
      arithmetics++;
    }
    else if (expValues[i] == 2) {
      logicals++;
    }
  }
  printf("Found %d expressions: %d logical and %d arithmetic\n", expressions, logicals, arithmetics);

  /*
  Key:
  0 = unexpected/empty
  1 = found
  2 = missing
  3 = unknown
  */
  for (i = 0; i < expressions; i++) {
    temp = expArray[i];

    if(expValues[i] == 1) {
      printArith(i, temp);
    }
    else if (expValues[i] == 2) {
      printLogic(i, temp);
    }
    else {
      printUnknown(i, temp);
    }
  }

  for (i = 0; i < expressions; i++) {
    temp = expArray[i];
    while (temp != NULL) {
      struct node *temp2 = temp;
      temp = temp->next;
      free(temp2);
    }
  }
  return 0;
}
