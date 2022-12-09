/*
 * server.h
 *
 *  Created on: Oct 24, 2022
 *      Author: omar hamdii
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "../terminal/terminal.h"

/*
 * Enum which Endicate Transection state
 */
typedef enum EN_transState_t
{
     APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;


/*
 * Enum which Endicate
 * card name
 * account number
 * card expire date
 * primaryAccountNumber
 * transAmount
 * maxTransAmount
 * transactionDate
 * transstate
 */
typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transStat_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction_t;


/*
 * Enum which endicate server error state
 */
typedef enum EN_serverError_t
{
     SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

/*
 * Enum which endicate Account state
 */
typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;


/*
 * structure Implement server-side accounts' database
 */
typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;



/*
 * Function Description :
 * This function will take all transaction data and validate its data, it contains all server logic.
 */
EN_serverError_t recieveTransactionData(ST_transaction_t *transData);


/*
 * Function Description :
 * This function will take card data and validate if the account related to this card exists or not.
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);


/*
 * Function Description :
 * This function takes a reference to the account into the database and verifies if it is blocked or not.
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);


/*
 * Function Description :
 * This function will take terminal data and a reference to the account in the database and check if the account has a sufficient amount to withdraw or not
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);


/*
 * Function Description :
 * This function will store all transaction data in the transactions database.
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData);



/*
 * Function Description :
 * This function prints all transactions found in the transactions DB
 */
void listSavedTransactions(void);


void update_accountbalance (void);



#endif /* SERVER_SERVER_H_ */
