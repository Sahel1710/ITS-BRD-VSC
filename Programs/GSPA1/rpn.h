#ifndef RPN_H
#define RPN_H



/**
 * @brief Hauptschleife des RPN-Rechners.
 * @details Liest kontinuierlich Tokens vom Scanner ein und delegiert 
 * die Ausfuehrung an die entsprechenden Rechen- oder Stack-Operationen. 
 * Koordiniert die Fehlerbehandlung bei ungueltigen Zustaenden.
 * @return void
 */
void runCalculator(void);

#endif // RPN_H