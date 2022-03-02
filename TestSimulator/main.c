#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define NE 28

int *exercises();
int randomValue(int lower, int upper);
void generateAnswers(char *answers, int *e);
void testSimulation(int *ex, char *answers, char *input);
void clearScreen();
int checkAnswer(char *string, int nAns);
int checkChoice(char *string);

int main()
{
    // VALUE OF EXERCISE MUST BE DIFFERENT FROM 46 , because 46 is missing //
    char *input = "Raccolta quiz.txt";
    int *randomExercises;
    char answers[NE];
    char choice[1024];
    int choiceOk = 0, choiceError = 0;
    int i, ok = 1, found=0, stop=0, simulationCounter=0;
    printf("******* Info : at the end of the test wrong answers will be highlighted by a 'X' symbol ******* \n");
    printf("******* < TestSimulator > by : Alessandro Vancini   ******* \n");
    while(stop==0){
    if(simulationCounter>0){
        clearScreen();
    }
    found=0;
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("___________________________________________________________________________________________________________________________________________________________________\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|TEST SIMULATION n.%*d|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n", 3,simulationCounter+1);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(found==0){
    srand( time(NULL));
    ok=1;
    randomExercises = exercises();
    for(i=0; i<NE; i++){
        if(randomExercises[i]<1 || randomExercises[i]>167){
            ok = 0;
        }
    }
    if(ok==1){
        found=1;
    }
    }

    generateAnswers(answers,randomExercises);

    testSimulation(randomExercises,answers,input);
    while( choiceOk == 0){
    if(choiceError == 1){
    printf("< Input error : type 'y' or 'n' or 'Y' or 'N' > \n");
    printf("\n");
          }
    printf("\n");
    printf("Repeat test? y/n : ");
    fgets(choice,1024,stdin);
    choiceOk = checkChoice(choice);
    if(choiceOk == 0){
        choiceError =  1;
    } else{
    choiceError = 0;
    choice[0] = tolower(choice[0]);
    if(choice[0] == 'n'){
        stop=1;
    }
    if(choice[0] == 'y'){
        // DO NOTHING = keep going //
    }
    }
    printf("\n");
    }
    choiceOk = 0;
    simulationCounter++;
    }
    return 0;
}

int *exercises(){
    int *array;
    int upper=6, lower=1;
    array = (int*)malloc(NE*sizeof(int));
    int i=0, randVal;
    srand( time(NULL));
    for(i=0; i<NE; i++){
        randVal = randomValue(lower,upper);
            if(randVal != 46 && randVal != 0){
            array[i] = randVal;
        }

        lower = upper+1;
        upper = upper + 6;
            if(upper>167){
                upper = 167;

            }
        }

    return array;
}

int randomValue(int lower, int upper){
int num = rand() % (upper-lower+1);
num = num+lower;
return num;
}

void generateAnswers(char *answers, int *e){
    FILE *quiz;
    char buffer[1024];
    int ex;
    int i = 0, waitR = 0;
    char *input = "Raccolta quiz.txt";
    char *token;
    quiz = fopen(input,"r");
    if(quiz == NULL){
        printf("Error, missing file : Raccolta quiz.txt\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer,1024,quiz) != NULL){

        if(buffer[0] == 'E' && waitR == 0){
            token = strtok(buffer,".");
            token = strtok(token," ");
            token = strtok(NULL," ");
            ex = atoi(token);
            if(ex == e[i]){
                waitR = 1;
            }
        } else
        if(buffer[0] == 'R' && waitR == 1){
            token = strtok(token," ");
            answers[i] = token[0];
            waitR = 0;
            i++;
        }
    }
    fclose(quiz);
}

void testSimulation(int *ex, char *answers, char *input){
    FILE *quiz;
    char buffer[1024], *tmp;
    char userAnswers[NE];
    char uAns[1024];
    int numberOfPossibleAnswers = 0;
    int exerciseN, correctAnswers=0, wrongAnswers=0;
    float estimatedMark;
    int i = 0, print=0, found=0, j=0, getComment=0;
    char *token;
    char **comments;
    int inputOk = 0, errorRepeat=0;
    comments = (char**)malloc(NE*sizeof(char*));
    quiz = fopen(input,"r");
    if(quiz == NULL){
        printf("Error, missing file : Raccolta quiz.txt\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer,1024,quiz) != NULL){

        if(buffer[0] == 'C' && buffer[1] == ':' && getComment == 1){
            comments[j-1] = strdup(buffer);
            getComment=0;
        }

        if(print == 1 && buffer[0] != 'R'){
            printf("%s", buffer);
            numberOfPossibleAnswers++;
            } else {
            if(found==1){
                    while(inputOk==0){
                            if(errorRepeat == 1){
                                    if(numberOfPossibleAnswers == 3){
                                    printf(" ~< Input error : type 'A' or 'B' or 'C' , 'a' or 'b' or 'c' >~ \n");
                                    } else if(numberOfPossibleAnswers == 4){
                                    printf(" ~< Input error : type 'A' or 'B' or 'C' or 'D' , 'a' or 'b' or 'c' or 'd' >~ \n");
                                    } else if(numberOfPossibleAnswers == 5){
                                    printf(" ~< Input error : type 'A' or 'B' or 'C' or 'D' or 'E', 'a' or 'b' or 'c' or 'd' or 'e' >~ \n");
                                    }
                            }
            printf("\n");
            printf(">} Choose an answer :  ");
            fgets(uAns,1024,stdin);
            inputOk = checkAnswer(uAns, numberOfPossibleAnswers);
            if(inputOk == 0){
                errorRepeat=1;
            } else
            {
                userAnswers[j] = uAns[0];
                errorRepeat = 0;
            }
                    }
            inputOk=0;
            printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
            printf("___________________________________________________________________________________________________________________________________________________________________\n");
            printf("\n");
            print = 0;
            found=0;
            getComment=1;
            j++;
            }
            numberOfPossibleAnswers = 0;
            }

        tmp = strdup(buffer);
        if(buffer[0] == 'E' && print == 0){
            token = strtok(buffer,".");
            token = strtok(token," ");
            token = strtok(NULL," ");
            exerciseN = atoi(token);
            if(exerciseN == ex[i]){
                printf("\n");
                printf("%d} %s", i+1,tmp);
                printf("\n");
                i++;
            print=1;
            found=1;
            }
        }
    }
    printf("~UserAnswers~      ~Answers~\n");
    // RESULTS OF THE TEST //
   for(i=0; i<NE; i++){
    if(answers[i] == userAnswers[i]){
        correctAnswers++;
        printf("%d)[%c]              >%c<\n", i+1,userAnswers[i], answers[i]);
    } else {
    wrongAnswers++;
        printf("%d)[%c] X            >%c<\n", i+1,userAnswers[i], answers[i]);
    }
   }
   printf("\n");
   if(wrongAnswers>0){
   printf("Comments of wrong answers : \n");
   printf("\n");
   for(i=0; i<NE; i++){
    if(answers[i] != userAnswers[i]){
        printf("%d) %s\n", i+1,comments[i]);
    }
 }
}
   printf("{~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}\n");
   printf("|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°[TEST RESULTS]°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|\n");
   printf("|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|\n");
   printf("|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°(Correct answers : %*d/%d)°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|\n", 2,correctAnswers, NE);
   estimatedMark = (1.07*correctAnswers)-(1.5*wrongAnswers);
   printf("|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°(Estimated exam mark : %*.2f/30)°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|\n", 6,estimatedMark);
   printf("|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|\n");
   printf("{~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}\n");

   // FREE ALLOCATED MEMORY FOR COMMENTS //
   for(i=0; i<NE; i++){
    free(comments[i]);
   }
}

void clearScreen(){
int i;
for(i=0; i<70; i++){
    printf("\n");
}
}

int checkAnswer(char *string, int nAns){
int length = strlen(string);
if((length)>2){
    return 0;
} else {
string[0] = toupper(string[0]);
if(nAns == 3){
if(string[0] != 'A' && string[0] != 'B' && string[0] != 'C'){
    return 0;
}
}
else if(nAns == 4){
if(string[0] != 'A' && string[0] != 'B' && string[0] != 'C' && string[0] != 'D'){
    return 0;
}
}
else if(nAns == 5){
if(string[0] != 'A' && string[0] != 'B' && string[0] != 'C' && string[0] != 'D' && string[0] != 'E'){
    return 0;
}
}
}
return 1;
}

int checkChoice(char *string){
int length = strlen(string);
if(length > 2){
    return 0;
} else {
if(string[0] != 'y' && string[0] != 'Y' && string[0] != 'n' && string[0] != 'N'){
    return 0;
} else {
return 1;
}
}
}
