/*
 * server.c
 *
 *  Created on: Oct 24, 2022
 *      Author: omar hamdii
 */
#include "server.h"

#define SERVER_DATABASE 255


/*******************************************************Global_variable**************************************/
static uint8_t counter = 0;

/*variable that store new acc of user after the transection*/
uint16_t new_amount ;


/*
 * variable that give number of account that stored in server data_base
 */
sint8_t number_of_account = -1 ;


uint8_t recievetrans ;

uint8_t is_valid_account ;

uint8_t is_blocked_account ;

uint8_t is_amount_available ;


/******************************************************************************************************/
/*
 * structure that we store account in server data_base
 */
extern ST_accountsDB_t accountsDB[SERVER_DATABASE] ={
		{50.0, RUNNING, "8989374615436851"},\
		{2000.0, RUNNING, "8569374615436851"} ,\
		{100.0, BLOCKED, "6787007076043875"},\
		{200.0, RUNNING, "9319374615436851"},\
		{200000.0, BLOCKED, "1347007076043875"},\
		{5000.0, RUNNING, "9069374615436851"},\
		{700000.0, BLOCKED, "6107007076043875"},\
		{90.0, RUNNING, "5349374615436851"},\
		{1200000.0, BLOCKED, "8507007076043875"},\
};




/*
 * server-side transactions' database
 */
ST_transaction_t client_transaction[SERVER_DATABASE] ;

/*************************************************Functions********************************************/


/*
 * Function Description :
 * This function will take all transaction data and validate its data, it contains all server logic.
 */
EN_serverError_t recieveTransactionData(ST_transaction_t *transData)
{

	uint8_t acc_valide;
	uint8_t acc_amount;
	uint8_t acc_saved;
	uint8_t acc_blocked;

	acc_valide = isValidAccount(&transData->cardHolderData , accountsDB);

	if (acc_valide == ACCOUNT_NOT_FOUND)
	{
		printf("Account is not found\n");
		recievetrans =0;
		return FRAUD_CARD;
	}

	acc_amount= isAmountAvailable(&transData->terminalData , accountsDB);
	if (acc_amount==LOW_BALANCE)
	{
		recievetrans =1;
		return DECLINED_INSUFFECIENT_FUND;
	}

	acc_saved=saveTransaction(transData);

	if (acc_saved =! SERVER_OK)
	{
		recievetrans =3;
		return INTERNAL_SERVER_ERROR;
	}
	 acc_blocked = isBlockedAccount(accountsDB);
	 if (acc_blocked== BLOCKED_ACCOUNT)
	 {
		return  DECLINED_STOLEN_CARD ;
	 }
	else
	{
		return SERVER_OK ;
	}
return SERVER_OK ;
}


/*
 * Description :
 *This function will take card data and validate if the account related to this card exists or not.
 */

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	uint8_t comp ;
	printf ("Input data %s \n" , cardData->primaryAccountNumber);
	for (uint8_t i=0 ; i<SERVER_DATABASE ; i++)
	{
		comp=strcmp (cardData->primaryAccountNumber ,accountRefrence[i].primaryAccountNumber);
		if (comp==0)
		{
			number_of_account = i ;
			printf ("account %d \n" , i);
			is_valid_account = 0;
			printf ("Expected Result %s\n" , accountRefrence[i].primaryAccountNumber);
			return SERVER_OK;
			break ;
		}

	}

	is_valid_account = 1;
	printf ("Expected Result : no account matched\n");
	return ACCOUNT_NOT_FOUND;
}

/********************************************************************************************************************/
/*
 * Description :
 *This function takes a reference to the account into the database and verifies if it is blocked or not.
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if (accountRefrence[number_of_account].state == BLOCKED )
	{
		is_blocked_account = 1;
		return BLOCKED_ACCOUNT;
	}
	else 	if (accountRefrence->state == BLOCKED )
	{
		is_blocked_account = 0;
		return SERVER_OK;
	}
}

/*************************************************************************************************************************/
/*
 * Description :
 *This function will take terminal data and a reference to the account in the database and check if the account has a sufficient amount to withdraw or not.
 */

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	uint16_t balance= accountRefrence[number_of_account].balance ;
	uint16_t amount = termData->transAmount ;

	if (accountsDB[0].balance < termData->transAmount)

	{
		is_amount_available = 1;
		return LOW_BALANCE;
	}
	else

	{

		new_amount = balance - amount ;

		is_amount_available = 0;
		return SERVER_OK;
	}
}
/***************************************************************************************************************/
/*
 *Function Description :
 *This function will store all transaction data in the transactions database.
 */

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{


	strcpy (client_transaction[counter].cardHolderData.cardExpirationDate , transData->cardHolderData.cardExpirationDate);

	strcpy (client_transaction[counter].cardHolderData.cardHolderName , transData->cardHolderData.cardHolderName);

	strcpy (client_transaction[counter].cardHolderData.primaryAccountNumber , transData[number_of_account].cardHolderData.primaryAccountNumber);

	client_transaction[counter].terminalData. transAmount = transData[number_of_account].terminalData.transAmount;

	client_transaction[counter].terminalData. maxTransAmount = transData->terminalData.maxTransAmount;

	strcpy (client_transaction[counter].terminalData.transactionDate , transData->terminalData.transactionDate);

	return SERVER_OK ;

	counter++;
}



/*********************************************Test_Function*****************************************/

void recieveTransactionDataTest (void)
{
	/*
	 * Function Description :
	 * function discripe card state
	 * FRAUD_CARD or APPROVED or INTERNAL_SERVER_ERROR or DECLINED_STOLEN_CARD or DECLINED_INSUFFECIENT_FUND
	 */
	switch (recievetrans)
	{
	printf ("Tester Name: Omar Hmady\n");
	printf ("Function Name: recieveTransactionData\n");
	case 0:
		printf ("FRAUD_CARD\n");
		printf ("/n");
		break;

	case 1:
		printf ("DECLINED_INSUFFECIENT_FUND\n");
		printf ("\n");
		break;


	case 2:
		printf ("DECLINED_STOLEN_CARD\n");
		printf ("\n");
		break;

	case 3:
		printf ("INTERNAL_SERVER_ERROR\n");
		printf ("\n");
		break;

	case 4:
		printf ("APPROVED\n");\
		printf ("\n");
		break;
	default:
		break;
	}
}

/****************************************************************************************************/

void isValidAccountTest(void)
{
	printf ("Tester Name: Omar Hmady \n");
	printf ("Function Name: isValidAccount \n");
	switch (is_valid_account)
	{
	case 0:
		printf ("Actual Result:SERVER_OK \n");
		printf (" \n");
		break;

	case 1:
		printf ("Actual Result:ACCOUNT_NOT_FOUND \n");
		printf (" \n");
		break;

	default:
		break;
	}
}

/******************************************************************************************************/

void isBlockedAccountTest(void)
{
	printf ("Tester Name:Omar Hamdy\n");
	printf ("Function Name: isBlockedAccount\n");

	switch (is_blocked_account) {
	case 0:
		printf ("SERVER_OK\n");
		printf (" \n");
		break;

	case 1:
		printf ("BLOCKED_ACCOUNT\n");
		printf ("\n");
		break ;

	default:
		break;
	}
}

/*********************************************************************************************************/

void isAmountAvailableTest(void)
{
	printf ("Tester Name:Omar Hamdy \n");
	printf ("Function Name: isAmountAvailable \n");
	switch (is_amount_available) {
	case 0:
		printf ("SERVER_OK \n");
		printf (" \n");
		break;

	case 1:
		printf ("LOW_BALANCE \n");
		printf (" \n");
		break ;

	default:
		break;
	}
}

/*********************************************************************************************************/

void saveTransactionTest(void)
{
	printf ("Tester Name:Omar Hamdy\n");
	printf ("Function Name:saveTransaction \n");
	printf ("SERVER_OK \n");
	printf (" \n");
}

/***********************************************************************************************************/
void listSavedTransactions(void)
{
	printf ("Transaction Sequence Number: %d \n" , number_of_account);

	printf ("Transaction Date: %s \n", client_transaction[counter].terminalData. transactionDate) ;


	printf ("Transaction Amount: %.1f \n" ,client_transaction[counter].terminalData.transAmount);

	if (new_amount>0)
	{
		printf ("money in account after transection %d \n" , new_amount);
	}

	printf ("Transaction State:" );
	if ( client_transaction[counter].transState==0)
	{
		printf ("TERMINAL_OK\n");
	}
	else if ( client_transaction[counter].transState==1)
	{
		printf ("WRONG_DATE\n");
	}
	else if ( client_transaction[counter].transState==2)
	{
		printf ("EXPIRED_CARD\n");
	}
	else if ( client_transaction[counter].transState==3)
	{
		printf ("INVALID_CARD\n");

	}
	else if ( client_transaction[counter].transState==4)
	{
		printf ("INVALID_AMOUNT\n");

	}
	else if ( client_transaction[counter].transState==5)
	{
		printf ("EXCEED_MAX_AMOUNT\n");

	}

	else if ( client_transaction[counter].transState==5)
	{
		printf ("INVALID_MAX_AMOUNT\n");

	}


	printf ("Terminal Max Amount: %.1f \n" ,client_transaction[counter].terminalData.maxTransAmount);


	printf ("Cardholder Name: %s \n" , client_transaction[counter].cardHolderData.cardHolderName);


	printf ("PAN: %s \n" ,  client_transaction[counter].cardHolderData.primaryAccountNumber  );


	printf ("Card Expiration Date: %s \n" , client_transaction[counter].cardHolderData.cardExpirationDate );
}
