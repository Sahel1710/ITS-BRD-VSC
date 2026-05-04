#ifndef ERROR_CODES_H
#define ERROR_CODES_H

/**
 * @brief Zentrale Definition aller Fehlerzustände des RPN-Rechners.
 * @details Negative Werte werden für Fehler verwendet, 0 signalisiert Erfolg.
 * Dies ermöglicht einfache Prüfungen wie 'if (status < 0)'.
 */

#define SUCCESS             0   /**< Operation erfolgreich abgeschlossen */
#define ERR_DIV_BY_ZERO    -1   /**< Division durch den Wert 0 versucht */
#define ERR_OVERFLOW       -2   /**< Positiver Ganzzahl-Überlauf (Ergebnis > INT_MAX) */
#define ERR_UNDERFLOW      -3   /**< Negativer Ganzzahl-Unterlauf (Ergebnis < INT_MIN) */
#define ERR_STACK_OVERFLOW -4   /**< Versuch, in einen vollen Stack zu schreiben */
#define ERR_STACK_UNDERFLOW -5  /**< Versuch, von einem leeren Stack zu lesen */

#endif // ERROR_CODES_H