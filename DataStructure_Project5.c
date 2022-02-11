///P5_1190707_LojainAbdalrazaq_3
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 350
#define INFINITY 99999
/*****
 In this project, i used the adjacency matrix to implement the graph
 and finding the shortest path between two nodes, because i used the
 adjacency list but the program didnt complied and i didnt get the expected
 results, so in order to have a program that works without any problem
 i moved to plan B, which is using the adjacency matrix and the program
 is finished compiled correctly, having the correct results...
*****/
int numOfAreas;
///first of all i made a struct that contains the cost
///or the weight (name of the city and the distance)
struct Cost
{
    int Dist;///distance
    char City_Name[40];///name of the city between each node

};

typedef struct Cost info;
///then i created an adjacency matrix of constant size
///max = 300->so it will be 300 X 300
info AdjMatrix[MAX][MAX];

///for reading and writing in the file
FILE *readInputs ;
FILE *writeOutputs;

///Functions
void readFile();
void Set_Zero();
void Valid(int,int);
void check();
void count();
void Dijkstra(info AdjMatrix[MAX][MAX],int,int);

int main()
{
    count();
    int Constant=1;
    ///for the while loop
    int area1;
    int area2;
    ///for the id that will be entered from the user

    ///Dispaly the menu for the user to choose
    printf("\n");
    printf("***********************************************************\n");
    printf("*      Please Select One of the Following Options         *\n");
    printf("***********************************************************\n");
    printf("* 1- Read the file and load the data.                     *\n");
    ///Reading the txt file->segments and loading the adjacency matrix.
    printf("* 2- Enter 2 points to calculate the shortest path.       *\n");
    ///using the function of Dijkstra we will calculate the shortest path
    ///between to cities or areas
    printf("* 3- Exit from the program.                               *\n");
    ///exiting from the program
    printf("***********************************************************\n");

    int user_option;
    scanf("%d",&user_option);

    while(Constant)
    {
        ///while loop will continue until the user press the 3rd option
        ///which is exiting the program

        if (user_option == 1)
        {
            ///if the user chose number 1 (1st option)
            ///then first of all
            ///we will set all the values of the matrix equal ZERO
            ///using -->(Set_Zero) function
            Set_Zero();

            ///then read the file using -->(readFile) function and load the values
            ///in the adjacency matrix
            readFile();
            printf("The file is read successfully\n\n");
        }
        else if (user_option == 2)
        {
            ///when the user choose the 2nd option
            ///then that means we need to find the shortest distance
            ///between two areas (or cities)
            ///and we are dealing with the numbers
            ///cities are known as numbers(ID)
            printf("Please enter the the 1st city (or area):\n");
            scanf("%d",&area1);
            ///entering the first id (source)
            printf("Please enter the the 2nd city (or area):\n");
            scanf("%d",&area2);
            ///entering the second id (destination)
            ///then
            ///calling the-->(valid) function
            ///this function check if the entered values
            ///of the id (from the user) is valid or not
            ///if it is not valid
            ///it ask the user to enter another 2 id values
            ///and keep checking if it valid or not
            Valid(area1,area2);

            ///calculate the shortest path between 2 areas
            ///and writhing the data in the (route) file
            Dijkstra(AdjMatrix,area2,area1);

            ///checking if the user want to enter another 2 id
            ///or not by using ->(check) function
            check();
        }
        ///now
        ///if the user chose to exit
        ///just exit and get out the loop
        else if (user_option == 3 )
        {
            printf("\n     process Finished   \n");
            printf("\n        Thank You       \n");
            break;
        }
        else
        {
            ///if the user chose any other options
            ///will print an error massage
            printf("Wrong Option...\n");
            printf("Please Choose again\n");
            printf("\n\n");
        }
        ///the menu appear again
        printf("\n");
        printf("***********************************************************\n");
        printf("*      Please Select One of the Following Options         *\n");
        printf("***********************************************************\n");
        printf("* 1- Read the file and load the data.                     *\n");
        printf("* 2- Enter 2 points to calculate the shortest path.       *\n");
        printf("* 3- Exit from the program.                               *\n");
        printf("***********************************************************\n");

        scanf("%d",&user_option);
    }

    return 0;
}
///this function set the values
///of the adjacency mateix equal zero
///in order to fill the values after reading the file
void Set_Zero()
{

    int i=0;
    ///using  loop
    ///seting all values to ZERO
    while(i< MAX)
    {
        int j=0;
        while(j< MAX)
        {
            ///all the values in the matrix is initially zero
            AdjMatrix[i][j].Dist = 0;
            j++;
        }
        i++;
    }
}

///this function check if the id entered are valid or not
///because we have range in the id
///its start from 1
///and end with 295
///so any values out of rage
///will be a problem
void Valid(int id1,int id2)
{

    ///the first loop check if multiple conditions
    ///if one of them happened
    ///then that means that there is invalid id entered
    ///and will ask the user to enter another two id
    ///and check it again recursively until the user
    ///enter the correct or valid id
    if( id1> numOfAreas ||id1 < 1 ||id2> numOfAreas ||id2 < 1)
    {
        printf("INVALID ID :(, please enter another two values.\n");
        ///the condition that i have put it is
        /// if the id > number of cities
        ///or less than 1
        ///then it will print an error massage
    }
    else if(id1<numOfAreas &&id1 > 0&&id2<numOfAreas&& id2 > 0)
    {
        ///if the entered values are correct
        ///then we dont do any thing
        return;
    }
    ///ask the user to enter another 2 values
    printf("Enter the first area again:\n");
    int area1,area2;
    scanf("%d\n",&area1);
    printf("Enter the second area again:\n");
    scanf("%d\n",&area2);

    ///checking recursively the id entered
    Valid(area1,area2);
    ///calling the (Dijkstra) function
    ///in order to find the shortest path between two id
    Dijkstra(AdjMatrix,area2,area1);

    ///calling the check function
    ///to check if the user want to enter another 2 id to calculate
    ///the shortest path between them
    check();
}

///This function will read inputs from the file
///and then, it will load the data to the adjMatrix
void readFile()
{


    readInputs = fopen("segments.txt", "r");
    ///opening the file

    ///initializing the variables
    ///for the source, destination
    ///and distance
    int source_city1;
    int destination_city2;
    int Dist;
    char line[100];

    ///If there is no file to open
    if(readInputs==NULL)
    {
        ///printing this error statment
        printf("error while opening the file\n");
    }
    ///if there wan no problem
    ///we start reading the file and loading the data
    else
    {

        while(fgets(line,100,readInputs)!=NULL)
        {

            char name[50]= " ";
            ///the name of the city

            char* address= strtok(line," ");
            ///splitting each line according to the space

            for(int counter=0; address!=NULL; counter++)
            {

                ///If the counter equals zero
                ///then it will be the first id
                if(counter==0)
                {
                    source_city1=(int)strtol(address,NULL,10);
                    ///then i converted the string to integer
                    ///and put in the source_city1 which represent the id of the 1st ciry

                }

                else  if (counter==1)
                    destination_city2=(int)strtol(address,NULL,10);
                ///now if the counter equals 1, then we have
                ///to do the same steps as we did before
                ///converting to integer and put in the destination_city2
                ///which represent the id of the 2nd area

                else
                {
                    ///else
                    ///then now, we are reading the name of the road
                    ///in this if statement
                    ///it will compare the first index of the string
                    ///if it was between the 0 and the 9
                    ///then we have read the distance between two node
                    if((strncmp(&(address[0]),"0",1))>=0 && (strncmp(&(address[0]),"9",1)<=0))
                        Dist=atoi(address);
                    ///converting the string into integer using the atoi function
                    ///storing the result in the (dist) variable
                    else
                    {
                        ///since we have words with space between the string
                        ///we use the function -> concat
                        ///to make concatenation between the name of the road between them
                        strcat(name,address);
                        strcat(name," ");
                    }
                }

                ///contenue the same steps in each line
                address = strtok(NULL," ");
            }
            ///since the matrix is undirected
            ///when we have a edge between two nodes
            ///for example city 1 - city 2
            ///we add the cost(weight) to 1-2
            ///and also at the same time we add
            /// from 2-1

            ///city 1,city 2
            AdjMatrix[source_city1][destination_city2].Dist= Dist;
            strcpy(AdjMatrix[source_city1][destination_city2].City_Name,name);
            ///city 2,city 1
            AdjMatrix[destination_city2][source_city1].Dist= Dist;
            strcpy(AdjMatrix[destination_city2][source_city1].City_Name,name);
            ///i used the -->strcpy function to copy the string

        }
    }

    ///All data are read from the file...
    ///closing the file....
    fclose(readInputs);
}
///in this function
///we check if the user want to enter more id
///to calulate the distance and print the shortest path
///between them
void check()
{

    ///initializing the variables
    char check_choice[3];
    int area1,area2;
    ///printing statement that ask the user to enter more values or not
    printf("Do you want to enter more ID to calculate the shortest path?\n");
    printf("please Enter one of the following (in lower case)\n");
    printf("->yes \n");
    printf("->no\n");
    ///so we have 2 options to chose
    scanf("%s",check_choice);

    if(strcasecmp(check_choice, "yes") == 0)
    {
        ///i used the--> strcasecmp function to compare between them
        ///if the user chose yes
        ///then we ask him to enter the values of id
        printf("\nEnter the source and the destination: \n");
        scanf("%d%d",&area1,&area2);

        ///after entering the values
        ///we call the function ->Valid
        ///to be sure about that the values are valid or not
        Valid(area1,area2);

        ///calling the ->Dijkstra Function in order to calculate the shortest path
        Dijkstra(AdjMatrix,area2,area1);

        ///recursive call to the same function to check if we want to enter more values
        check();
    }
    else
    {
        ///if the answer was no
        ///we just exit and get our the function
        return;
    }
}

///in this function
///we will calculate the max value of the id
///in order to handle any mistake if the user enter invalid value
void count()
{

    ///Now, opening the segments again
    FILE *readInputs = fopen("segments.txt","r");

    char string[MAX];
    ///initializing the integer value
    ///that will increase
    ///to be the number of cities or (areas)
    int temp =0;

    while (fgets(string,1000,readInputs)!=NULL)
    {
        char *tok[90];
        ///starting at count->0
        int count =0;
        ///now, we will split according to the space
        char *Split = strtok(string," ");
        tok [count]=Split;
        ///now for loop for splitting
        ///and putting the results in the ->tok
        for (count; Split != NULL; ++count)
        {
            Split=strtok(NULL," ");
            tok [count]=Split;
        }
        int area1;
        int area2;
        ///here, i converted the sting to the integer
        ///using-> strtol function
        ///to decide which values is the bigger
        area1 = (int)strtol(tok[0],NULL,10);
        ///area 1 will take the first value
        area2 = (int)strtol(tok[1],NULL,10);
        ///area 2 will take the second value

        ///if statement check if the id of area1 is less than area2
        if(area1<area2)
        {
            ///if the id is less than
            ///then we check for the temp
            ///if the temp is less
            ///we put the value of area 2 in temp
            if(temp <area2)
            {
                temp = area2;
            }
        }
        ///if area 1 is bigger
        else if (area1>=area2)
        {
            ///we check for the temp value
            ///if it was less
            ///then we put it as the value of area 2
            if(temp <area1)
            {
                temp =area1;
            }
        }


    }
    ///closing the input file
    fclose(readInputs);
    ///setting the maximum value of the areas (id)
    ///or cities equals the max. value that has read from the file
    ///in numOfAreas
    numOfAreas = temp;
}

///in this function
///we will calculate the shortest path between 2 areas
///and also print the path between them
///on the screen and in the route file
void Dijkstra(info AdjMatrix[MAX][MAX], int area1,int area2)
{

    writeOutputs = fopen("route.txt","a");
    ///open the route file to write in it

    int cost[MAX][MAX];
    ///we will use these variables to save put the shortest path between the 2 area
    ///and determined if the node (vertex) is visited or not
    int dis[MAX];
    int pr[MAX];
    int reach[MAX];
    int count,i, j;
    ///initializing variables
    int  mdist, next;

    char print_option[3];

    ///this while loop performs the initial values of each node
    i = 0;
    while (i < MAX)
    {
        j = 0;
        while(j <MAX)
        {
            ///if the AdjMatrix[i][j].Dist equals to zero
            ///that means we didint read from the file any direct connection
            ///so the values stay as what initially be
            ///which is the zero
            if (AdjMatrix[i][j].Dist == 0)
            {
                cost[i][j] = INFINITY;
            }

            else
                ///else
                ///the value is read from the file
                ///and we have a direct connection between the two areas
                cost[i][j] = AdjMatrix[i][j].Dist;
            j++;///increase 1
        }
        i++;///increase 1
    }
    i = 0;
    while (i <MAX)
    {
        ///this while loop start at i=0
        ///and continue until the maximum value
        ///siting the values of dis[i]
        dis[i] = cost[area1][i];
        pr[i] = area1;
        reach[i] = 0;
        i++;
    }

    dis[area1] = 0;
    reach[area1] = 1;
    count = 1;

    while (count <MAX- 1)
    {
        ///so if the count is less than the max-1
        mdist = INFINITY;
        ///setting the mdist equals to zero
        i = 0;
        while (i <MAX)
        {
            ///the dist[i] less the mdist
            ///and it did not visited
            if (dis[i] < mdist && !reach[i])
            {
                ///putting mdist equals the distance and the value of next equals to i
                mdist = dis[i];
                next= i;
            }
            i++;//increasing by 1
        }

        reach[next] = 1;
        for ( i = 0; i <MAX; i++)
            if (!reach[i])
                if (mdist + cost[next][i] < dis[i])
                {
                    /// in this loop if the mdis and the cost
                    ///less than the distance
                    ///we update and set the values of distance equals the sum
                    dis[i] = mdist + cost[next][i];

                    pr[i] = next;

                }
        count++;///increase by 1
    }

    ///if the user enter the same id
    ///for the two areas
    ///then the distance will zero
    ///because the distance from area to itself equals zero
    if (area2 == area1)
    {
        printf("area 1 that has id-> %d and area 2 that has id->%d are the same\n",area1,area2);
        printf("so the distance will be zero\n");
        printf("\n----------------------------------------------------------------\n");
        printf("Do you want to save the result in the route file?\n");
        printf("Please Enter yes or no (in lower case)\n");
        char save_option[3];
        scanf("%s",save_option);
        ///used-> strcasecmp function to check if the answer is yes
        if(strcasecmp(save_option, "yes") == 0)
        {
            ///printing in the file the distance value between the two areas(which is the same)->0
            fprintf(writeOutputs,"\nThe distance between %d and %d is 0",area1,area2);
        }
    }
    else
    {
        ///if the first area does not equal the second area
        ///then we check the dis[area2]
        ///if it was infinity
        ///that means there is no path between the two areas
        if (dis[area2] == INFINITY)
        {
            printf("\n There is no path between %d and %d",area1,area2);
            return;
            ///get out of the function
        }
        ///if there was a path between the two areas
        ///then we print it
        ///printing the shortest distance
        printf("The distance between  %d  and %d equal: %d\n\n",area1,area2,dis[area2]);
        printf("The PATH between the tow areas is: \n");
        j=area2;

        ///this do while loop is for printing the path
        ///with the name of the countries between the two cities
        do
        {
            ///printing the path
            printf("->%s",AdjMatrix[j][pr[j]].City_Name);
            j = pr[j];

        }
        while(j!= area1);

        ///now, after printing the path on screen
        ///we ask the user to decide if save the data inside the rout file or not
        printf("\n----------------------------------------------------------------\n");
        printf("\nDo you want to print in the route file?\n");
        printf("Please Enter yes or no.(in lower case)\n");
        char save_option[3];
        scanf("%s",&save_option);
        ///using-> strcasecmp function
        ///we check if the answer is yes or no
        if(strcasecmp(save_option, "yes") == 0)
        {
            ///if it was yes
            ///then, we print or save the path between each two ares in the route file
            printf("\n----------------------------------------------------------------\n");
            fprintf(writeOutputs,"\nThe distance between  %d  and %d equal: %d\n",area1,area2,dis[area2]);
            fprintf(writeOutputs,"Path : \n");
            j=area2;
            do
            {
                ///printing the path
                fprintf(writeOutputs,"->%s",AdjMatrix[j][pr[j]].City_Name);
                j = pr[j];

            }
            while(j!= area1);
        }

    }

    printf("\n");
    ///closing the route file
    fclose(writeOutputs);

}