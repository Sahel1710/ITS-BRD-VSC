#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

/**
 * @brief Zentraler Einstiegspunkt für die Fehlerbehandlung.
 * @details Nimmt einen Fehlercode entgegen, schaltet das System in den 
 * Fehlermodus, gibt eine Meldung aus und sichert die Hardware-Ressourcen.
 * @param errCode Der zu verarbeitende Fehlercode aus error_codes.h.
 */
void handle_error(int errCode);

#endif // ERRORHANDLER_H