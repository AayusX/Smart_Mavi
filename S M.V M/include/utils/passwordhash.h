#ifndef PASSWORDHASH_H
#define PASSWORDHASH_H

#include <QObject>
#include <QString>
#include <QCryptographicHash>
#include <QByteArray>
#include <QRandomGenerator>
#include <QRegularExpression>

class PasswordHash : public QObject
{
    Q_OBJECT

public:
    explicit PasswordHash(QObject *parent = nullptr);
    
    // Password hashing
    static QString hashPassword(const QString &password);
    static bool verifyPassword(const QString &password, const QString &hash);
    
    // Password generation
    static QString generateRandomPassword(int length = 12);
    static QString generateStrongPassword();
    static QString generateMemorablePassword();
    
    // Password validation
    static bool isStrongPassword(const QString &password);
    static bool isValidPassword(const QString &password);
    static QString getPasswordStrength(const QString &password);
    
    // Password requirements
    static bool hasMinimumLength(const QString &password, int minLength = 8);
    static bool hasUppercase(const QString &password);
    static bool hasLowercase(const QString &password);
    static bool hasNumbers(const QString &password);
    static bool hasSpecialCharacters(const QString &password);
    static bool hasNoCommonPatterns(const QString &password);
    
    // Security utilities
    static QString generateSalt();
    static QString combinePasswordAndSalt(const QString &password, const QString &salt);
    static QString extractSaltFromHash(const QString &hash);
    static QString extractHashFromCombined(const QString &combined);
    
    // Password policy
    static void setPasswordPolicy(int minLength, bool requireUppercase, bool requireLowercase,
                                 bool requireNumbers, bool requireSpecialChars);
    static void getPasswordPolicy(int &minLength, bool &requireUppercase, bool &requireLowercase,
                                 bool &requireNumbers, bool &requireSpecialChars);

private:
    // Password policy settings
    static int s_minLength;
    static bool s_requireUppercase;
    static bool s_requireLowercase;
    static bool s_requireNumbers;
    static bool s_requireSpecialChars;
    
    // Helper methods
    static QByteArray generateRandomBytes(int length);
    static QString bytesToHex(const QByteArray &bytes);
    static QByteArray hexToBytes(const QString &hex);
    static QString getCommonPasswords();
    static QString getCommonPatterns();
    
    // Validation helpers
    static bool containsCommonPassword(const QString &password);
    static bool containsCommonPattern(const QString &password);
    static bool hasRepeatingCharacters(const QString &password);
    static bool hasSequentialCharacters(const QString &password);
    
    // Character sets
    static QString getUppercaseChars();
    static QString getLowercaseChars();
    static QString getNumberChars();
    static QString getSpecialChars();
    static QString getVowelChars();
    static QString getConsonantChars();
};

// For QVariant support
Q_DECLARE_METATYPE(PasswordHash)

#endif // PASSWORDHASH_H
