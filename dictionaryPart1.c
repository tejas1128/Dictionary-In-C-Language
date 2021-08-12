#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int lenOfDict = 0;

struct node
{
    char data[200];
    struct node *link;
};

struct node *headKey = NULL, *headValue = NULL;

int checkKeyValue(char keyValue[200])
{
    if (headKey == NULL)
    {
        return -1;
    }

    struct node *temp = headKey;
    int count = 0;
    while (temp != NULL)
    {
        if (!strcmp(temp->data, keyValue))
        {
            return count;
        }
        count++;
        temp = temp->link;
    }

    return -1;
}

int getKeyData(char keyData[200])
{
    struct node *newkeydata;
    newkeydata = (struct node *)malloc(sizeof(struct node));

    strcpy(newkeydata->data, keyData);
    newkeydata->link = NULL;

    if (headKey == NULL)
    {
        headKey = newkeydata;
    }

    else
    {
        struct node *temp = headKey;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = newkeydata;
    }

    return 1;
}

int getValueData()
{
    char valueValue[200];

    struct node *newValueData;
    newValueData = (struct node *)malloc(sizeof(struct node));

    printf("Enter the value: ");
    scanf("%[^\n]s", newValueData->data);
    newValueData->link = NULL;

    if (headValue == NULL)
    {
        headValue = newValueData;
    }

    else
    {
        struct node *temp = headValue;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = newValueData;
    }

    lenOfDict++;
    return 1;
}

void insertData()
{
    char keyValue[200];
    int keyPresent = -1, keyProcess = 0, valueProcess = 0;

    printf("Enter the key: ");
    scanf("%[^\n]s", keyValue);
    // scanf("%s", keyValue);
    getchar();

    keyPresent = checkKeyValue(keyValue);

    if (keyPresent != -1)
    {
        printf("\nKey is already present\nTry with a different key :<\n");
        return;
    }

    else
    {
        keyProcess = getKeyData(keyValue);
        if (keyProcess)
        {
            valueProcess = getValueData();
            if (valueProcess)
            {
                printf("\nData inserted successfully :)\n");
                return;
            }
            else
            {
                printf("\nSome internal Error :(\n");
            }
        }
        else
        {
            printf("\nSome internal Error :(\n");
            return;
        }
    }
}

void display(int choice)
{
    if (headKey == NULL || headValue == NULL)
    {
        printf("\nNo items in the dictionary\n");
        return;
    }

    else
    {
        struct node *tempKey = headKey;
        struct node *tempValue = headValue;
        if (choice == 2)
        {
            while (tempKey != NULL || tempValue != NULL)
            {
                printf("( %s : ", tempKey->data);
                printf("%s )", tempValue->data);
                printf("\n");
                tempKey = tempKey->link;
                tempValue = tempValue->link;
            }
        }

        else if (choice == 3)
        {
            printf("[ ");
            while (tempKey != NULL)
            {
                printf(" %s ,", tempKey->data);
                tempKey = tempKey->link;
            }
            printf(" ]");
        }

        else if (choice == 4)
        {
            printf("[ ");
            while (tempValue != NULL)
            {
                printf(" %s ,", tempValue->data);
                tempValue = tempValue->link;
            }
            printf(" ]");
        }

        else if (choice == 5)
        {
            printf("{ ");
            while (tempKey != NULL || tempValue != NULL)
            {
                printf("( %s : ", tempKey->data);
                printf("%s ) , ", tempValue->data);
                tempKey = tempKey->link;
                tempValue = tempValue->link;
            }
            printf(" }");
        }
    }
}

int delAtBeg()
{
    struct node *temp;

    temp = headKey;
    headKey = temp->link;
    temp->link = NULL;
    free(temp);

    temp = headValue;
    headValue = temp->link;
    temp->link = NULL;
    free(temp);

    return 1;
}

int delAtEnd()
{
    struct node *temp, *prev;
    temp = headKey;
    while(temp->link!=NULL)
    {
        prev = temp;
        temp = temp->link;
    }

    if(temp == headKey)
    {
        headKey = NULL;
    }
    else
    {
        prev->link = NULL;
    }
    free(temp);


    temp = headValue;
    while(temp->link!=NULL)
    {
        prev = temp;
        temp = temp->link;
    }

    if(temp == headValue)
    {
        headValue = NULL;
    }
    else
    {
        prev->link = NULL;
    }
    free(temp);


    return 1;
}

int delAtPos(int index)
{
    int i=0;
    struct node *temp, *prev;

    temp = headKey;
    while(i<index)
    {
        prev = temp;
        temp = temp->link;
        i++;
    }
    prev->link = temp->link;
    temp->link = NULL;
    free(temp);

    i=0;
    temp = headValue;
    while(i<index)
    {
        prev = temp;
        temp = temp->link;
        i++;
    }
    prev->link = temp->link;
    temp->link = NULL;
    free(temp);

    return 1;

}

void delItem()
{
    char delKey[200];
    int keyPresent = -1;

    if(lenOfDict == 0)
    {
        printf("\nCurrently there is no items to delete :)");
        return;
    }

    printf("Enter the key of item you want to delete: ");
    scanf("%[^\n]s",delKey);
    getchar();

    keyPresent = checkKeyValue(delKey);

    if(keyPresent == -1)
    {
        printf("\nNo data with this key to delete : %s",delKey);
        return;
    }

    else
    {
        int delSuccess = 0;
        if(keyPresent == 0)
        {
            delSuccess = delAtBeg();
        }
        else if(keyPresent == lenOfDict-1)
        {
            delSuccess = delAtEnd();
        }
        else
        {
            delSuccess = delAtPos(keyPresent);
        }

        if(delSuccess == 1)
        {
            printf("\nRecord successfully deleted :)\n");
            lenOfDict--;
        }
        else
        {
            printf("\nSome internal Error :(\n");
        }
        
    }

}

int main()
{
    int choice = -1;
    printf("Dictionay In C");

    while (1)
    {
        printf("\n\n\n1. dict['key'] = value\n2. for item in dict.items()\n3. dict.keys()\n4. dict.values()\n5. print(dict)\n6. del dict['key']\n7. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
            case 1:
                getchar();
                insertData();
                break;

            case 2:
            case 3:
            case 4:
            case 5:
                display(choice);
                break;

            case 6:
                getchar();
                delItem();
                break;

            case 7:
                exit(0);
        }

        // printf("Length : %d\n",lenOfDict);
    }
}