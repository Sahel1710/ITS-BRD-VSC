#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

/**
 * @brief Legt einen Wert auf den Stack.
 * @param value Der zu speichernde Integer-Wert.
 * @return SUCCESS bei Erfolg, ERR_Stack_Overflow wenn kein Platz mehr ist.
 */
int push(int value);

/**
 * @brief Entnimmt das oberste Element vom Stack.
 * @param value Pointer auf den Speicherbereich, in den das Ergebnis geschrieben wird.
 * @return SUCCESS bei Erfolg, ERR_Stack_Underflow wenn der Stack leer ist.
 */
int pop(int *value);

/**
 * @brief Setzt den Stack-Pointer zurueck und leert den Stack logisch.
 */
void clearStack(void);

/**
 * @brief Liefert die aktuelle Anzahl der Elemente auf dem Stack.
 * @return Anzahl der Elemente (0 bis MAX_STACK_SIZE).
 */
int getStackSize(void);

/**
 * @brief Liest ein Element an einem bestimmten Index, ohne den Stack zu veraendern.
 * @param index Position (0 = unterstes Element).
 * @param value Pointer fuer den gelesenen Wert.
 * @return SUCCESS oder ERR_Stack_Underflow bei ungueltigem Index.
 */
int getStackElement(int index, int *value);

#endif // STACK_H