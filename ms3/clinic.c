/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Sevinj Feyziyeva
Student ID#: 154057194
Email      : sfeyziyeva@myseneca.ca
Section    : NJJ

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

int NumberOfDays(int year, int month)
{
    int D = 0;
    int Y = year;
    int N = month;
    if (N == 1 || N == 3 || N == 5
        || N == 7 || N == 8 || N == 10
        || N == 12) {
        D = 31;
    }

    // Check for 30 Days
    else if (N == 4 || N == 6
        || N == 9 || N == 11) {
        D = 30;
    }

    // Check for 28/29 Days
    else if (N == 2) {
        if (Y % 4 == 0) {
            if (Y % 100 == 0)
            {
                if (Y % 400 == 0)
                {
                    D = 29;
                }
                else
                {
                    D = 28;
                }
            }
            else
            {
                D = 29;
            }

        }
        else {
            D = 28;
        }
    }
    return D;
}
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do
    {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{

    int selection;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:

            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }

    } while (selection != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i;
    int newPatientIndex = -1, nextAvailablePatientNumber;

    for (i = 0; (i < max) && newPatientIndex == -1; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            newPatientIndex = i; //if patientNum is = 0 setting newPatientIndex to the current array 
        }
    }
    if (newPatientIndex == -1) // if empty elements not found
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else {
        nextAvailablePatientNumber = nextPatientNumber(patient, max);
        patient[newPatientIndex].patientNumber = nextAvailablePatientNumber;
        inputPatient(&patient[newPatientIndex]);
        printf("*** New patient record added ***\n");
    }

    putchar('\n');
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNumber, patientIndex;

    printf("Enter the patient number: ");
    scanf(" %d", &patientNumber);
    putchar('\n');

    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientIndex == -1) { //means the patient with given num was not found
        printf("ERROR: Patient record not found!\n");
    }
    else {
        menuPatientEdit(&patient[patientIndex]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    // get the patient number as user input
    printf("Enter the patient number: ");
    int num = inputInt();
    // using the patient number, get the index in the patient array
    int index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');
    // if index is -1, patient number is not existing
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)\n", patient[index].phone.description);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        char answer;
        answer = inputCharOption("yn");
        if (answer == 'n')
        {
            printf("Operation aborted.\n");
        }
        else
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
    }
    putchar('\n');
}
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    // allocate memory for temp array
    struct Appointment* temp = (struct Appointment*)calloc(data->maxAppointments, sizeof(struct Appointment));
    // transfer appointments array to temp
    for (i = 0; i < data->maxAppointments; i++)
    {
        temp[i].patientData = data->appointments[i].patientData;
        temp[i].date = data->appointments[i].date;
        temp[i].time = data->appointments[i].time;
    }
    // sort temp array
    bubbleSort(temp, data->maxAppointments);
    displayScheduleTableHeader(&(temp->date), 1);
    // display the required output
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (temp[i].patientData.patientNumber != 0)
        {
            int index = findPatientIndexByPatientNum(temp[i].patientData.patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &temp[i], 1);
        }
    }
    putchar('\n');
    free(temp);
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int year;
    int month;
    int day;
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    /*if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (1-29)  : ");
        day = inputIntRange(1, 29);
    }
    else
    {
        printf("Day (1-28)  : ");
        day = inputIntRange(1, 28);
    }*/
    day = NumberOfDays(year, month);
    printf("Day (1-%d)  : ", day);
    day = inputIntRange(1, day);
    putchar('\n');
    struct Date inputDate;
    inputDate.year = year;
    inputDate.month = month;
    inputDate.day = day;
    displayScheduleTableHeader(&inputDate, 0);
    int i;
    // allocate memory for temp array
    struct Appointment* temp = (struct Appointment*)calloc(data->maxAppointments, sizeof(struct Appointment));
    // transfer appointments array to temp
    for (i = 0; i < data->maxAppointments; i++)
    {
        temp[i].patientData = data->appointments[i].patientData;
        temp[i].date = data->appointments[i].date;
        temp[i].time = data->appointments[i].time;
    }
    // sort temp array
    bubbleSort(temp, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (temp[i].patientData.patientNumber != 0
            && temp[i].date.year == inputDate.year
            && temp[i].date.month == inputDate.month
            && temp[i].date.day == inputDate.day)
        {
            int index = findPatientIndexByPatientNum(temp[i].patientData.patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &temp[i], 0);
        }
    }
    putchar('\n');
    free(temp);
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* apps, int maxApps, struct Patient* patients, int maxPatients)
{
    int patientNum;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int i;
    int flag = 0;
    int full = 1;

    // check if appointment array is not yet full
    for (i = 0; i < maxApps; i++)
    {
        if (apps[i].patientData.patientNumber < 1)
        {
            full = 0;
            break;
        }
    }
    // if full, display error message and exit the function
    if (full == 1)
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
        return;
    }
    printf("Patient Number: ");
    patientNum = inputIntPositive();
    // validate entered patient number
    int index = findPatientIndexByPatientNum(patientNum, patients, maxPatients);
    // if patient number is not found, display error message and exit the function
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        return;
    }
    // enter the required data for a new appointment and check for data validity
    while (1)
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (1-12): ");
        month = inputIntRange(1, 12);
        /* if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
         {
             printf("Day (1-29)  : ");
             day = inputIntRange(1, 29);
         }
         else
         {
             printf("Day (1-28)  : ");
             day = inputIntRange(1, 28);
         }*/
        day = NumberOfDays(year, month);
        printf("Day (1-%d)  : ", day);
        day = inputIntRange(1, day);
        printf("Hour (0-23)  : ");
        hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        minute = inputIntRange(0, 59);
        // check if timeslot is already existing in the appointment array
        for (i = 0; i < maxApps; i++)
        {
            if (apps[i].date.year == year &&
                apps[i].date.month == month &&
                apps[i].date.day == day &&
                apps[i].time.hour == hour &&
                apps[i].time.min == minute)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
                flag = 0;
                break;
            }
            flag = 1;
        }
        if (flag == 0)
            continue;
        while (1)
        {
            // check if timeslot is withing operational hours and is a valid interval
            int input = hour * 60 + minute;
            if (input % INTERVAL != 0 || input < START_HOUR * 60 + START_MIN || input > END_HOUR * 60 + END_MIN)
            {
                printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n\n",
                    START_HOUR, START_MIN, END_HOUR, END_MIN, INTERVAL);
                printf("Hour (0-23)  : ");
                hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                minute = inputIntRange(0, 59);
                flag = 0;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    // add the appointment
    for (i = 0; i < maxApps; i++)
    {
        if (apps[i].patientData.patientNumber < 1)
        {
            apps[i].patientData.patientNumber = patientNum;
            apps[i].date.year = year;
            apps[i].date.month = month;
            apps[i].date.day = day;
            apps[i].time.hour = hour;
            apps[i].time.min = minute;
            break;
        }
    }
    printf("\n*** Appointment scheduled! ***\n");
    putchar('\n');
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* apps, int maxApps, struct Patient* patients, int maxPatients)
{
    int patientNum;
    int year;
    int month;
    int day;
    int i;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    // validate entered patient number
    int index = findPatientIndexByPatientNum(patientNum, patients, maxPatients);
    // if patient number is not found, display error message and exit the function
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        return;
    }
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (1-29)  : ");
        day = inputIntRange(1, 29);
    }
    else
    {
        printf("Day (1-28)  : ");
        day = inputIntRange(1, 28);
    }
    putchar('\n');
    // show the detailed information about the patient
    printf("Name  : %s\n", patients[index].name);
    printf("Number: %05d\n", patients[index].patientNumber);
    printf("Phone : ");
    displayFormattedPhone(patients[index].phone.number);
    printf(" (%s)\n", patients[index].phone.description);
    printf("Are you sure you want to remove this appointment (y,n): ");
    char answer;
    answer = inputCharOption("yn");
    // cancel removing the appointment
    if (answer == 'n')
    {
        printf("Operation aborted.\n");
    }
    // remove the appointment
    else
    {
        for (i = 0; i < maxApps; i++)
        {
            if (apps[i].patientData.patientNumber == patientNum &&
                apps[i].date.year == year &&
                apps[i].date.month == month &&
                apps[i].date.day == day)
            {
                apps[i].patientData.patientNumber = 0;
                break;
            }
        }
        printf("\nAppointment record has been removed!\n");
    }
    putchar('\n');
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    // get the patient number as user input
    printf("Search by patient number: ");
    int num = inputInt();
    // using the patient number, get the index in the patient array
    int index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');

    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        // call the displayPatientData() using the index in the patient array
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');

}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[PHONE_LEN + 1];
    int i, phoneSearch = 0;

    printf("Search by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();

    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            phoneSearch = 1;
        }
    }

    if (phoneSearch == 0)
    {
        printf("\n*** No records found ***\n");
    }
    else {
        for (i = 0; i < max; i++) {
            if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    putchar('\n');
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestPatientNumber = 0, i; // check if pat num index is higher than the highestPatientNumber to change highestPatientNumber to that one.
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > highestPatientNumber)
        {
            highestPatientNumber = patient[i].patientNumber;
        }
    }
    return (highestPatientNumber + 1);
}
// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    {
        int i;

        for (i = 0; i < max; i++)
        {
            if (patientNumber == patient[i].patientNumber)
                return i; //return to matching index
        }
    }
    return -1; //if matches not found
}

//////////////////////////////////////
// 

// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    // get the patient info as user input
    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);

    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("\nContact: CELL\n");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("\nContact: HOME\n");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("\nContact: WORK\n");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "\0");
        break;
    }
    putchar('\n');
}
//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int counter = 0;

    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[counter].patientNumber,
            patients[counter].name,
            patients[counter].phone.description,
            patients[counter].phone.number) != EOF)
        {
            counter++;
            if (counter >= max)
                break;
        }
    }
    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
        exit(1);
    }
    return counter;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int counter = 0;

    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[counter].patientData.patientNumber,
            &appoints[counter].date.year,
            &appoints[counter].date.month,
            &appoints[counter].date.day,
            &appoints[counter].time.hour,
            &appoints[counter].time.min) != EOF)
        {
            counter++;
            if (counter >= max)
                break;
        }
    }
    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
        exit(1);
    }
    return counter;
}

// Swap two Appointment struct elements
void swap(struct Appointment* x, struct Appointment* y)
{
    struct Appointment temp = *x;
    *x = *y;
    *y = temp;
}

// Implement bubble sort
void bubbleSort(struct Appointment arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
        {
            long long data1 = arr[j].date.year * 12 * 30 * 24 * 60 + arr[j].date.month * 30 * 24 * 60 + arr[j].date.day * 24 * 60 + arr[j].time.hour * 60 + arr[j].time.min;
            long long data2 = arr[j + 1].date.year * 12 * 30 * 24 * 60 + arr[j + 1].date.month * 30 * 24 * 60 + arr[j + 1].date.day * 24 * 60 + arr[j + 1].time.hour * 60 + arr[j + 1].time.min;
            if (data1 > data2)
                swap(&arr[j], &arr[j + 1]);
        }
}