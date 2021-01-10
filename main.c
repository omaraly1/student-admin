#include "summative.h"

void gotoxy(int x,int y) {
    COORD c= {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
//https://social.msdn.microsoft.com/Forums/vstudio/en-US/62cd20db-c911-48b2-b48b-b20c78a93d22/get-cursor-position-and-its-character-in-console-application?forum=vcgeneral
void getConsoleInfo(int* x, int* y) {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
        printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
    *x = screenBufferInfo.dwMaximumWindowSize.X;
    *y = screenBufferInfo.srWindow.Bottom;
}

int main(void)
{
    system("COLOR 7");

    int studentCount = 0, courseCount = 0, teacherCount = 0;
    int index = 0;
    int ret;
    Student students[400];
    Course courses[100];
    Teacher teachers[100];
    int width, height;
    int input1, input2, input3, input4;

    getConsoleInfo(&width, &height);

    gotoxy(width/2 - 3, height/2);
    printf("Welcome\n");

    gotoxy(0, height);
    system("PAUSE");



    studentCount = loadStudents(students);
    courseCount = loadCourses(courses);
    teacherCount = loadTeachers(teachers);

    do {

        input1 = mainMenu();

        switch(input1) {
        case 0:
            input1 = displayStudents(students, courses, &studentCount, courseCount);
            break;
        case 1:
            input1 = displayAllCourses(teachers, courses, students, teacherCount, courseCount, studentCount);
            break;
        case 2:
            input1 = displayTeachers(teachers, courses, &teacherCount, courseCount);
            break;
        }


    } while(input1 != -100);
    // displayStudents(students, studentCount);
    saveCourses(courses, courseCount);
    saveTeachers(teachers, teacherCount);
    saveStudents(students, studentCount);
    system("cls");
    printf("Goodbye!");
    Sleep(1000);





    return 0;
}

int mainMenu()
{
    char* options[20] = {"Students","Courses","Teachers"};
    char* commands[] = {};
    int input = 0;

    input = displayItems("Welcome to Omar's Students Tracking System!","To get started, please select of the following to view,",
                         commands,NULL,options,1,3,0,0);

    return input;

}


int loadStudents(Student *stud)
{
    int i = 0;

    FILE *fp;

    char fileName[50] = "summ-students.txt";
    fp = fopen(fileName,"r+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;
    }

    else {
        while(!feof(fp)) {
            fscanf(fp,"%s %s %i\n",stud[i].firstName, stud[i].lastName, &stud[i].studentID);
            i++;
        }
        fclose(fp);

        printf("Student file data loaded properly.\n");
    }


    return i;

}

int loadCourses(Course *courses)
{

    int i = 0, j = 0, x = 0;

    FILE *fp;

    char fileName[50] = "summ-courses.txt";
    fp = fopen(fileName,"r+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;
    }

    else {
        while(!feof(fp)) {
            fscanf(fp,"%i %s %[^\n]s",&courses[i].courseID, courses[i].courseCode, courses[i].courseName);
            fscanf(fp,"%i %i", &courses[i].numStudents, &courses[i].period);
            for(j=0; j<courses[i].numStudents; j++) {
                fscanf(fp,"%i",&courses[i].studentID[j]);
            }
            for(x=0; x<courses[i].numStudents; x++) {
                fscanf(fp,"%i",&courses[i].mark[x]);
            }

            if (strlen(courses[i].courseName)!=0){
                i++;
            }
        }
        fclose(fp);
        printf("Course file data loaded properly.\n");
    }

    return i;
}

int loadTeachers(Teacher *teachers)
{
    int i = 0, j = 0;

    FILE *fp;

    char fileName[50] = "summ-teachers.txt";
    fp = fopen(fileName,"r+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;
    }

    else {
        while(!feof(fp)) {
            fscanf(fp,"%i %s %[^\n]s",&teachers[i].teacherID, teachers[i].firstName, teachers[i].lastName);
            fscanf(fp,"%i",&teachers[i].numCourses);
            for (j=0; j<teachers[i].numCourses; j++) {
                fscanf(fp,"%i",&teachers[i].courseID[j]);
            }

            if (strlen(teachers[i].firstName)!=0 || strlen(teachers[i].lastName) != 0){
                i++;
            }

        }
        fclose(fp);

        printf("Teacher file data loaded properly.\n");


    }
    return i;

}



int saveStudents(Student *students, int numStudents)
{
    int i = 0;

    FILE *fp;

    char fileName[50] = "SAVESTUDENTS.txt";
    fp = fopen(fileName,"w+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;
    }

    else {
        for(i=0; i<numStudents; i++) {
            fprintf(fp,"%s %s %i\n",students[i].firstName, students[i].lastName, students[i].studentID);
        }
        fclose(fp);
        printf("Student file data saved properly.\n");
        return 1;
    }



}

int saveCourses(Course *courses, int numCourses)
{
    int i = 0, j = 0, x = 0;

    FILE *fp;

    char fileName[50] = "COURSESAVE.txt";
    fp = fopen(fileName,"w+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;
    }

    else {
        for (i=0; i<numCourses-1; i++) {
            fprintf(fp,"%i %s %s\n",courses[i].courseID, courses[i].courseCode, courses[i].courseName);
            fprintf(fp,"%i %i\n", courses[i].numStudents, courses[i].period);

            for(j=0; j<courses[i].numStudents-1; j++) {
                fprintf(fp,"%i ",courses[i].studentID[j]);
            }
            fprintf(fp,"%i\n",courses[i].studentID[j]);


            for(x=0; x<courses[i].numStudents-1; x++) {
                fprintf(fp,"%i ",courses[i].mark[x]);
            }
            fprintf(fp,"%i\n",courses[i].mark[x]);

        }
        fclose(fp);

        printf("Course file data saved properly.\n");
        return 1;
    }



}

int saveTeachers(Teacher *teachers, int numTeachers)
{
    int i = 0, j = 0;

    FILE *fp;

    char fileName[50] = "SAVETEACHERS.txt";
    fp = fopen(fileName,"w+");

    if (fp == NULL) {
        printf("File was not loaded properly.\n");
        return 0;

    }

    else {
        for (i=0; i<numTeachers-1; i++) {
            fprintf(fp,"%i %s %s\n",teachers[i].teacherID, teachers[i].firstName, teachers[i].lastName);
            fprintf(fp,"%i\n",teachers[i].numCourses);
            for (j=0; j<teachers[i].numCourses-1; j++) {
                fprintf(fp,"%i ",teachers[i].courseID[j]);
            }
            fprintf(fp,"%i\n",teachers[i].courseID[j]);
        }
        fclose(fp);

        printf("Teacher file data saved properly.\n");
        return 1;
    }

}

void sortStudentsByFirstName(Student *stud, int numStudents)
{

    int i, sort=1;

    Student temp;
    do {
        sort = 0;
        for (i=0; i<numStudents-1; i++)
        {
            if(strcmp(stud[i].firstName,stud[i+1].firstName)>0)
            {
                temp = stud[i];
                stud[i] = stud[i+1];
                stud[i+1] = temp;
                sort = 1;
            }
        }
    } while(sort == 1);

}

void sortStudentsByLastName(Student *stud, int numStudents)
{

    int i, sort=1;

    Student temp;
    do {
        sort = 0;
        for (i=0; i<numStudents-1; i++)
        {
            if(strcmp(stud[i].lastName,stud[i+1].lastName)>0)
            {
                temp = stud[i];
                stud[i] = stud[i+1];
                stud[i+1] = temp;
                sort = 1;
            }
        }
    } while(sort == 1);

}
void sortCoursesByName(Course *courses, int numCourses)
{

    int i, sort=1;

    Course temp;
    do {
        sort = 0;
        for (i=0; i<numCourses-1; i++)
        {
            if(strcmp(courses[i].courseName,courses[i+1].courseName)>0)
            {
                temp = courses[i];
                courses[i] = courses[i+1];
                courses[i+1] = temp;
                sort = 1;
            }
        }
    } while(sort == 1);

}

void sortTeachersByLastName(Teacher *teachers, int numTeachers)
{

    int i, sort=1;

    Teacher temp;
    do {
        sort = 0;
        for (i=0; i<numTeachers-2; i++)
        {
            if(strcmp(teachers[i].lastName,teachers[i+1].lastName)>0)
            {
                temp = teachers[i];
                teachers[i] = teachers[i+1];
                teachers[i+1] = temp;
                sort = 1;
            }
        }
    } while(sort == 1);

}




int addStudent(Student *students, Student *newStudent, int numStudents)
{
    if (numStudents < 400) {
        students[numStudents] = *newStudent;
        return 1;
    } else {
        // Print an error
        return 0;
    }
}

int removeFromCourse(Course *course, Student *stud)
{
    int j=0, found = 0, x=0;

    for (j=0; j<course->numStudents && found == 0; j++) {
        if (course->studentID[j] == stud->studentID) {
            found = 1;
            for (x=j; x<course->numStudents-1; x++) {
                course->studentID[x] = course->studentID[x+1];
                course->mark[x] = course->mark[x+1];
            }
        }
    }

    course->numStudents--;

}

int deleteStudent (Student* stud, Course *courses, int index, int* numStudents, int numCourses)
{
    int i=0, j=0, x=0, found=0;
if (index < *numStudents) {
    for (i=0; i<numCourses; i++) {
        removeFromCourse(&courses[i],&stud[index]);
    }

        for (i=index; i<*numStudents-1; i++) {
            stud[i] = stud[i+1];
        }
        (*numStudents)--;
        return 1;
    } else {
        // Print an error
        return 0;
    }
}

int editItem (int index, char *input)
{
    int startX = 25, startY = 6;

    gotoxy(startX, startY+index);

    printf("                                                                                          ");
    gotoxy(startX, startY+index);
    scanf("%s",input);

}
void printItems (char* title, char* subtitle, char** commands, char** items, char ** labels, int edit,int count, int commandCount, int pageStart, int pageSize, int searchable, char* searchTerm)
{

    int i=0, j=0,x=0;

    int index = 0;
    int oldIndex;
    int ch = 0;
    int startX = 3, startY = 6;
    int width, height;
    char *staticCommands[10];
    int staticCount = 2;
    staticCommands[0] = "E-Exit";
    staticCommands[1] = "B-Back";
    int lineNumber;
    int pageCount = count/pageSize;

    if (count % pageSize > 0){
        pageCount++;
    }

    getConsoleInfo(&width, &height);

    if (searchable == 1) {
        staticCommands[staticCount] = "S-Search";
        staticCount++;
    }
    if (pageStart != 0) {
        staticCommands[staticCount] = "P-Previous";
        staticCount++;
    }
    if (pageStart + pageSize < count) {
        staticCommands[staticCount] = "N-Next";
        staticCount++;
    }



    system("cls");

    printf("%s\n\n",title);
    printf("%s\n",subtitle);

    for (i=pageStart; i<pageStart+pageSize && i<count; i++) {
        lineNumber = i-pageStart;
        gotoxy(startX, startY + lineNumber);
        if (edit==1) {
            printf("[   ] ");
        }
        else {
            printf("      ");
        }
        if (labels != NULL) {
            printf("%s",labels[i]);
        }
        if (items != NULL) {


            gotoxy(startX+22, startY + lineNumber);
            printf("%s",items[i]);
        }
        if (pageCount > 1){
        gotoxy( width-30, 3);
        printf("Page # %i / %i - %i records",(pageStart/pageSize+1),pageCount, count);
        }
    }
    if (count <= 0){
    gotoxy(startX, startY);
        printf("No records found...");
    }


    if (searchTerm != NULL) {
        gotoxy(7, 28);
        printf("Search Term: %s",searchTerm);

    }
    else {
        for (j=0; j<commandCount; j++) {
            gotoxy(7+j*12, 28);
            printf("%i-%s ",j,commands[j]);
        }

        for (j=0; j<staticCount; j++) {
            gotoxy(width-60+j*12, 28);
            printf("%s ",staticCommands[j]);

        }
        gotoxy(startX + 2, startY + index);
    }


}

int filerItems(char ** labels,int count,char **filteredLabels,int *searchIndex, char* searchTerm )
{
    int i=0;
    char temp1[100];
    char temp2[100];
    int filteredCount=0;
    if (searchTerm != NULL)
    {


    strcpy(temp1, searchTerm);

    strlwr(temp1);
    }
    for (i=0; i<count; i++){
        if (searchTerm != NULL)
    {
        strcpy(temp2,labels[i]);
        strlwr(temp2);
    }
        if (searchTerm == NULL || strstr(temp2, temp1)!=NULL){
            filteredLabels[filteredCount] = labels[i];
            searchIndex[filteredCount] = i;
            filteredCount++;
        }
    }
    return filteredCount;
}
int displayItems(char* title, char* subtitle, char** commands, char** items, char ** labels, int edit,
                 int count, int commandCount, int searchable) {

    int i=0, j=0,x=0;

    int index = 0;
    int oldIndex;
    int ch = 0;
    int startX = 3, startY = 6;
    int width, height;
    int maxCount = 15;
    int pageStart = 0;
    int lineNumber;
    char searchTermData[100]="";
    char* searchTerm = NULL;
    char *filteredLabels[500];
    int searchIndex[500];
    int filteredCount;



    getConsoleInfo(&width, &height);
    filteredCount = filerItems(labels,count,filteredLabels,searchIndex,searchTerm);
    printItems(title,subtitle,commands,items,filteredLabels, edit,filteredCount,commandCount,pageStart,maxCount,searchable,searchTerm);

     if (edit == 1 && filteredCount > 0) {
            gotoxy(startX + 2, startY + index);
            printf("X");
            gotoxy(startX + 2, startY + index);

        }
    while(ch != 13) {

        ch = getch();
        oldIndex = index;
        switch(ch) {

        case 80:
            if (index+pageStart < filteredCount-1 && index < maxCount-1) {
                index++;
            }
            break;
        case 72:

            if (index > 0) {
                index--;
            }
            break;
        case 13:
            if (edit==1) {
                return searchIndex[index+pageStart];
            }
            break;

        default:
        {

            if (searchTerm != NULL) {
                if (isprint(ch) && strlen(searchTerm)<100){
                    searchTerm[strlen(searchTerm)] = ch;
                    searchTerm[strlen(searchTerm)+1] = '\0';
                    filteredCount = filerItems(labels,count,filteredLabels,searchIndex,searchTerm);
                    pageStart = 0;
                    index = 0;
                    printItems(title,subtitle,commands,items,filteredLabels, edit,filteredCount,commandCount,pageStart,maxCount,searchable,searchTerm);
                }
                else if (ch == 8 && strlen(searchTerm)!=0){
                    searchTerm[strlen(searchTerm)-1] = '\0';
                    filteredCount = filerItems(labels,count,filteredLabels,searchIndex,searchTerm);
                    pageStart = 0;
                    index = 0;
                    printItems(title,subtitle,commands,items,filteredLabels, edit,filteredCount,commandCount,pageStart,maxCount,searchable,searchTerm);
                }
                else if (ch == 27){
                    searchTerm = NULL;
                    filteredCount = filerItems(labels,count,filteredLabels,searchIndex,searchTerm);
                    pageStart = 0;
                    index = 0;
                    printItems(title,subtitle,commands,items,filteredLabels, edit,filteredCount,commandCount,pageStart,maxCount,searchable,searchTerm);
                }
            }
            else {
                ch = tolower(ch);
                switch(ch) {
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                    return 48-ch-1;

                case'e':
                    return -100;

                case'b':
                    return -200;


                case'n':
                    if (pageStart + maxCount < count) {
                        pageStart+=maxCount;
                        printItems(title,subtitle,commands,items,labels, edit,count,commandCount,pageStart,maxCount,searchable,searchTerm);
                    }
                    break;
                case'p':
                    if (pageStart>0) {
                        pageStart-=maxCount;
                        printItems(title,subtitle,commands,items,labels, edit,count,commandCount,pageStart,maxCount,searchable,searchTerm);
                    }
                    break;
                case's':
                    if (searchable == 1) {
                        searchTerm = searchTermData;
                        printItems(title,subtitle,commands,items,labels, edit,count,commandCount,pageStart,maxCount,searchable,searchTerm);
                    }
                    break;
                }
            }
        }
        }
        if (edit == 1 && filteredCount > 0) {
            gotoxy(startX + 2, startY + oldIndex);
            printf(" ");
            gotoxy(startX + 2, startY + index);
            printf("X");
            gotoxy(startX + 2, startY + index);

        }
        if (searchTerm != NULL) {
            gotoxy(7, 28);
            printf("Search Term: %s",searchTerm);

        }
    }

}


int displayStudents(Student *stud, Course *courses, int* numStudents, int numCourses)
{
    char* students [*numStudents];
    char studentBuffer[*numStudents][100];
    int i=0;
    int input, index;

    char* commands[10] = {};

    sortStudentsByLastName(stud, *numStudents);



    do {
        for (i=0; i<*numStudents; i++) {
            students[i] = studentBuffer[i];
            sprintf(students[i],"%i - %s, %s",stud[i].studentID, stud[i].lastName, stud[i].firstName);
        }

        input = displayItems("Student list!", "Please select the student you would like to view", commands, NULL, students,1,*numStudents,0,1);
        switch(input) {
        case -100:
        case -200:
            break;

        default:
            index = input;
            input = displayOneStudent(&stud[input], courses, *numStudents, numCourses);
            if (input == -300) {
                deleteStudent(stud, courses, index, numStudents, numCourses);

            }
            if (input == -200){
                //we need to ignore going back to the main function
                input = -201;
            }
            break;
        }


    } while(input != -100 && input != -200);

    return input;

}
int displayTeachers(Teacher *teachers, Course *courses, int* numTeachers, int numCourses)
{
    char* teach [*numTeachers];
    char teacherBuffer[*numTeachers][100];
    int i=0;
    int input, index;

    char* commands[10] = {};

   sortTeachersByLastName(teachers, *numTeachers);



    do {
        for (i=0; i<*numTeachers; i++) {
            teach[i] = teacherBuffer[i];
            sprintf(teach[i],"%i - %s, %s",teachers[i].teacherID, teachers[i].lastName, teachers[i].firstName);
        }

        input = displayItems("Teachers list!", "Please select the teacher you would like to view.", commands, NULL, teach,1,*numTeachers,0,1);
        switch(input) {
        case -100:
        case -200:
            break;

       default:
            index = input;
            input = displayOneTeacher(&teachers[input], courses, numCourses);

            if (input == -200){
                //we need to ignore going back to the main function
                input = -201;
            }

            break;



        }


    } while(input != -100 && input != -200);

    return input;

}

int displayCourses(Course *courses, int numCourses, int periodIndex)
{
    int i=0, j=0, input, count=0;

    char* courseDetails[numCourses];
    char coursesBuffer[numCourses][100];
    int courseIndex[numCourses];

    char* format = "%s %s -> Period: %i";


    sortCoursesByName(courses,numCourses);


    for (i=0; i<numCourses; i++) {
        if (periodIndex < 0 || periodIndex+1 == courses[i].period) {
            courseDetails[count] = coursesBuffer[count];
            courseIndex[count] = i;
            sprintf(courseDetails[count],format,courses[i].courseName,courses[i].courseCode,courses[i].period);
            count++;
        }
    }

    input = displayItems("Courses list!", "Please select a course.", NULL, NULL, courseDetails,1,count,0,1);

    if (input >= 0) {
        return courseIndex[input];
    }

    return input;

}

int displayOneCourse(Teacher *teachers, Course *course, Student *stud, int numTeachers, int numCourses, int numStudents)
{
    char* oneCourse[numStudents];
    char courseBuffer[numStudents][200];
    int i, j, x, input, count=0, found=0;
    float average=0;

    oneCourse[count] = courseBuffer[count];
    sprintf(oneCourse[count],"Course Name & Code: %s %s",course->courseName, course->courseCode);
    count++;
    oneCourse[count] = "";
    count++;

    oneCourse[count] = courseBuffer[count];
    sprintf(oneCourse[count],"Period: %i",course->period);
    count++;
    oneCourse[count] = "";
    count++;



    for (i=0; i<course->numStudents; i++){
        average += course->mark[i];
    }
    average = (float)average/(float)course->numStudents;
    oneCourse[count] = courseBuffer[count];
    sprintf(oneCourse[count],"Average mark of the class: %.2f %%",average);
    count++;
    oneCourse[count] = "";
    count++;

    for (i=0; i<numTeachers && found == 0; i++){
        for (j=0; j<teachers[i].numCourses && found == 0; j++){
            if (teachers[i].courseID[j] == course->courseID){
                oneCourse[count] = courseBuffer[count];
                sprintf(oneCourse[count],"Teacher - ID: %i - %s, %s\n\n", teachers[i].teacherID, teachers[i].lastName, teachers[i].firstName);
                count++;
                found = 1;
            }
        }
    }

    oneCourse[count] = "";
    count++;

    for (i=0; i<numStudents; i++){
        for (j=0; j<course->numStudents; j++){
        if (stud[i].studentID == course->studentID[j]){
                oneCourse[count] = courseBuffer[count];
                sprintf(oneCourse[count],"Student - ID: %i - %s, %s with a mark of %i %%", stud[i].studentID, stud[i].lastName, stud[i].firstName, course->mark[j]);
                count++;
            }
        }
    }




    return displayItems("Course Details...", "Viewing specific course...", NULL,NULL,oneCourse,0,count,0,0);

}

int displayAllCourses(Teacher *teachers, Course *courses, Student *stud, int numTeachers, int numCourses, int numStudents)
{
    int input, input2;

    do{
    input = displayCourses(courses, numCourses, -1);



       switch(input) {
        case -100:
        case -200:
            break;

       default:
    input = displayOneCourse(teachers, &courses[input], stud, numTeachers, numCourses, numStudents);

            if (input == -200){
                //we need to ignore going back to the main function
                input = -201;
            }

            break;
        }

    } while(input != -100 && input != -200);

    return input;



}

int displayOneStudent(Student *stud, Course *courses, int numStudents, int numCourses)
{

 int i=0, j=0, x=2, input=0, input2=0, edit = 0, commandCount = 2, realCommandCount=2, editCommandCount =1, periodIndex;
    int periodClass[4];
    int periodClassMark[4];

    char* schedule[10];
    char *labels[10] = {
        "   First Name:",
        "    Last Name:",
        "     Period 1:",
        "         Mark:",
        "     Period 2:",
        "         Mark:",
        "     Period 3:",
        "         Mark:",
        "     Period 4:",
        "         Mark:"
    };

    char* format = "%s %s";
    char* markFormat = "%i";

    char* commands[] = {"Edit","Delete"};
    char* editCommands[] = {"Done"};
    char** realCommands = commands;
    char editInput[100];




    do {
        schedule[0] = stud->firstName;
        schedule[1]=stud->lastName;

        for (i=0; i<numCourses && x<10; i++) {
            for (j=0; j<courses[i].numStudents && x<10; j++) {
                if (courses[i].studentID[j] == stud->studentID) {
                    x = courses[i].period-1;
                    periodClass[x] = i;
                    periodClassMark[x] = j;
                    x = x*2+2;
                    schedule[x] = malloc(strlen(format)+3+strlen(courses[i].courseName) + strlen(courses[i].courseCode)+1);
                    sprintf(schedule[x],format,courses[i].courseName,courses[i].courseCode);
                    x++;
                    schedule[x] = malloc(strlen(markFormat)+5);
                    sprintf(schedule[x],markFormat,courses[i].mark[j]);


                }
            }
        }

        input =  displayItems("Student Details...", "To edit a student, select edit and the field you would like to change", realCommands, schedule,labels,edit,10,realCommandCount,0);
        switch(input) {
        case -1:
            if (edit == 0) {
                edit = 1;
                realCommands = editCommands;
                realCommandCount = editCommandCount;
            }
            else {
                edit = 0;
                realCommands = commands;
                realCommandCount = commandCount;

            }

            break;
        case -100:
            return -100;
        case -200:
            return -201;

            break;
        case -2:
            input = -300;
            break;

            break;

        default:

            switch(input) {
            case 0:
                editItem (input,editInput);
                strcpy(stud->firstName, editInput);
                break;
            case 1:
                editItem (input,editInput);
                strcpy(stud->lastName, editInput);
                break;
            case 3:
            case 5:
            case 7:
            case 9:
                editItem (input,editInput);
                periodIndex = (input-3)/2;
                courses[periodClass[periodIndex]].mark[periodClassMark[periodIndex]] = atoi(editInput);
                break;
            case 2:
            case 4:
            case 6:
            case 8:
                periodIndex = (input-2)/2;
                input2 = displayCourses(courses, numCourses,periodIndex);

                removeFromCourse(&courses[periodClass[periodIndex]],stud);
                courses[input2].studentID[courses[input2].numStudents] = stud->studentID;
                courses[input2].mark[courses[input2].numStudents] = 0;
                courses[input2].numStudents++;
                break;


            }
            break;
        }

    } while(input != -100 && input != -200 && input != -300);


    for (i=2; i<10; i++) {
        if (schedule[i] != NULL)
            free(schedule[i]);
    }

    return input;


}


int displayOneTeacher(Teacher *teach, Course *courses, int numCourses)
{
    int i = 0, j = 0, x = 0, input= 0, input2 = 0, edit = 0, commandCount = 1, realCommandCount= 1, editCommandCount = 1, periodIndex, count = 6;
    int periodClass[4] = {0,0,0,0};
    int periodClassMark[4];

    char* schedule[6];
    char scheduleBuffer[6][100];
    char *labels[6] = {
        "   First Name:",
        "    Last Name:",
        "     Period 1:",
        "     Period 2:",
        "     Period 3:",
        "     Period 4:",
    };

    char* commands[] = {"Edit"};
    char* editCommands[] = {"Done"};
    char** realCommands = commands;
    char editInput[100];
    char* format = "%s %s";

    for (i=2; i<6; i++){
            schedule[i] = "NO CLASS";
        }


    do{

        schedule[x] = teach->firstName;
        x++;
        schedule[x] = teach->lastName;
        x++;


        for (i=0; i<numCourses && x<6; i++){
            for (j=0; j<teach->numCourses && x<6; j++){
            if (teach->courseID[j] == courses[i].courseID){
                x = courses[i].period+1;
                periodClass[x-2] = i;
                schedule[x] = scheduleBuffer[x];
                sprintf(schedule[x],format,courses[i].courseName,courses[i].courseCode);
                x++;

            }
            }
        }

        if (edit == 1){
            count = 2;
        }

        input =  displayItems("Teacher Details...", "To edit a teacher, select edit and the field you would like to change.", realCommands, schedule,labels,edit,count,realCommandCount,0);


        switch(input) {
        case -1:
            if (edit == 0) {
                edit = 1;
                realCommands = editCommands;
                realCommandCount = editCommandCount;
            }
            else {
                edit = 0;
                realCommands = commands;
                realCommandCount = commandCount;
                count = 6;

            }

            break;
        case -100:
            return -100;
        case -200:
            return -201;

            break;
        case -2:
            input = -300;
            break;

            break;

        default:

            switch(input) {
            case 0:
                editItem (input,editInput);
                strcpy(teach->firstName, editInput);
                break;
            case 1:
                editItem (input,editInput);
                strcpy(teach->lastName, editInput);
                break;
            /*
            case 2:
            case 3:
            case 4:
            case 5:
                periodIndex = (input-2)/2;
                input2 = displayCourses(courses, numCourses,periodIndex);

                teach->courseID[]
                break;


            }
            break;

        */
        }
    }

    } while(input != -100 && input != -200 && input != -300);



    return input;


}

