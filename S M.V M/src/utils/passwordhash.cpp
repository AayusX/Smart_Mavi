#include "utils/passwordhash.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QRandomGenerator>
#include <QRegularExpression>

// Static member initialization
int PasswordHash::s_minLength = 8;
bool PasswordHash::s_requireUppercase = true;
bool PasswordHash::s_requireLowercase = true;
bool PasswordHash::s_requireNumbers = true;
bool PasswordHash::s_requireSpecialChars = false;

PasswordHash::PasswordHash(QObject *parent)
    : QObject(parent)
{
}

QString PasswordHash::hashPassword(const QString &password)
{
    // Generate a random salt
    QString salt = generateSalt();
    
    // Combine password and salt
    QString combined = combinePasswordAndSalt(password, salt);
    
    // Hash the combined string using SHA-256
    QByteArray hash = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256);
    
    // Return salt + hash as hex string
    return salt + bytesToHex(hash);
}

bool PasswordHash::verifyPassword(const QString &password, const QString &hash)
{
    if (hash.length() < 64) return false; // Minimum hash length
    
    // Extract salt and hash
    QString salt = hash.left(32); // First 32 characters are salt
    QString storedHash = hash.mid(32); // Rest is the hash
    
    // Recreate the hash with the provided password
    QString combined = combinePasswordAndSalt(password, salt);
    QByteArray newHash = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256);
    QString newHashHex = bytesToHex(newHash);
    
    return storedHash == newHashHex;
}

QString PasswordHash::generateRandomPassword(int length)
{
    QString password;
    QString chars = getUppercaseChars() + getLowercaseChars() + getNumberChars() + getSpecialChars();
    
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        password += chars.at(index);
    }
    
    return password;
}

QString PasswordHash::generateStrongPassword()
{
    QString password;
    
    // Ensure at least one character from each required set
    if (s_requireUppercase) {
        password += getUppercaseChars().at(QRandomGenerator::global()->bounded(getUppercaseChars().length()));
    }
    if (s_requireLowercase) {
        password += getLowercaseChars().at(QRandomGenerator::global()->bounded(getLowercaseChars().length()));
    }
    if (s_requireNumbers) {
        password += getNumberChars().at(QRandomGenerator::global()->bounded(getNumberChars().length()));
    }
    if (s_requireSpecialChars) {
        password += getSpecialChars().at(QRandomGenerator::global()->bounded(getSpecialChars().length()));
    }
    
    // Fill the rest with random characters
    QString allChars = getUppercaseChars() + getLowercaseChars() + getNumberChars() + getSpecialChars();
    while (password.length() < s_minLength) {
        password += allChars.at(QRandomGenerator::global()->bounded(allChars.length()));
    }
    
    // Shuffle the password
    QString shuffled;
    while (!password.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(password.length());
        shuffled += password.at(index);
        password.remove(index, 1);
    }
    
    return shuffled;
}

QString PasswordHash::generateMemorablePassword()
{
    QStringList words = {"apple", "banana", "cherry", "dragon", "eagle", "forest", "garden", "house", "island", "jungle"};
    QString word = words.at(QRandomGenerator::global()->bounded(words.length()));
    
    // Capitalize first letter
    word[0] = word[0].toUpper();
    
    // Add a number
    word += QString::number(QRandomGenerator::global()->bounded(100));
    
    // Add a special character
    word += getSpecialChars().at(QRandomGenerator::global()->bounded(getSpecialChars().length()));
    
    return word;
}

bool PasswordHash::isStrongPassword(const QString &password)
{
    return isValidPassword(password) && getPasswordStrength(password) == "Strong";
}

bool PasswordHash::isValidPassword(const QString &password)
{
    return hasMinimumLength(password, s_minLength) &&
           (!s_requireUppercase || hasUppercase(password)) &&
           (!s_requireLowercase || hasLowercase(password)) &&
           (!s_requireNumbers || hasNumbers(password)) &&
           (!s_requireSpecialChars || hasSpecialCharacters(password)) &&
           hasNoCommonPatterns(password);
}

QString PasswordHash::getPasswordStrength(const QString &password)
{
    int score = 0;
    
    // Length bonus
    if (password.length() >= 8) score += 1;
    if (password.length() >= 12) score += 1;
    if (password.length() >= 16) score += 1;
    
    // Character variety bonus
    if (hasUppercase(password)) score += 1;
    if (hasLowercase(password)) score += 1;
    if (hasNumbers(password)) score += 1;
    if (hasSpecialCharacters(password)) score += 1;
    
    // Penalty for common patterns
    if (containsCommonPassword(password)) score -= 2;
    if (containsCommonPattern(password)) score -= 1;
    if (hasRepeatingCharacters(password)) score -= 1;
    if (hasSequentialCharacters(password)) score -= 1;
    
    if (score >= 6) return "Strong";
    if (score >= 4) return "Medium";
    if (score >= 2) return "Weak";
    return "Very Weak";
}

bool PasswordHash::hasMinimumLength(const QString &password, int minLength)
{
    return password.length() >= minLength;
}

bool PasswordHash::hasUppercase(const QString &password)
{
    return password.contains(QRegularExpression("[A-Z]"));
}

bool PasswordHash::hasLowercase(const QString &password)
{
    return password.contains(QRegularExpression("[a-z]"));
}

bool PasswordHash::hasNumbers(const QString &password)
{
    return password.contains(QRegularExpression("[0-9]"));
}

bool PasswordHash::hasSpecialCharacters(const QString &password)
{
    return password.contains(QRegularExpression("[!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>\\/?]"));
}

bool PasswordHash::hasNoCommonPatterns(const QString &password)
{
    return !containsCommonPassword(password) && 
           !containsCommonPattern(password) &&
           !hasRepeatingCharacters(password) &&
           !hasSequentialCharacters(password);
}

QString PasswordHash::generateSalt()
{
    return bytesToHex(generateRandomBytes(16));
}

QString PasswordHash::combinePasswordAndSalt(const QString &password, const QString &salt)
{
    return password + salt;
}

QString PasswordHash::extractSaltFromHash(const QString &hash)
{
    return hash.left(32);
}

QString PasswordHash::extractHashFromCombined(const QString &combined)
{
    return combined.mid(32);
}

void PasswordHash::setPasswordPolicy(int minLength, bool requireUppercase, bool requireLowercase,
                                    bool requireNumbers, bool requireSpecialChars)
{
    s_minLength = minLength;
    s_requireUppercase = requireUppercase;
    s_requireLowercase = requireLowercase;
    s_requireNumbers = requireNumbers;
    s_requireSpecialChars = requireSpecialChars;
}

void PasswordHash::getPasswordPolicy(int &minLength, bool &requireUppercase, bool &requireLowercase,
                                    bool &requireNumbers, bool &requireSpecialChars)
{
    minLength = s_minLength;
    requireUppercase = s_requireUppercase;
    requireLowercase = s_requireLowercase;
    requireNumbers = s_requireNumbers;
    requireSpecialChars = s_requireSpecialChars;
}

QByteArray PasswordHash::generateRandomBytes(int length)
{
    QByteArray bytes;
    bytes.resize(length);
    
    for (int i = 0; i < length; ++i) {
        bytes[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }
    
    return bytes;
}

QString PasswordHash::bytesToHex(const QByteArray &bytes)
{
    return bytes.toHex();
}

QByteArray PasswordHash::hexToBytes(const QString &hex)
{
    return QByteArray::fromHex(hex.toUtf8());
}

QString PasswordHash::getCommonPasswords()
{
    return "password,123456,123456789,qwerty,abc123,password123,admin,letmein,welcome,monkey";
}

QString PasswordHash::getCommonPatterns()
{
    return "qwerty,asdfgh,zxcvbn,123456,654321,111111,000000,aaaaaa,zzzzzz";
}

bool PasswordHash::containsCommonPassword(const QString &password)
{
    QString commonPasswords = getCommonPasswords();
    QStringList passwords = commonPasswords.split(",");
    
    for (const QString &common : passwords) {
        if (password.toLower().contains(common)) {
            return true;
        }
    }
    
    return false;
}

bool PasswordHash::containsCommonPattern(const QString &password)
{
    QString commonPatterns = getCommonPatterns();
    QStringList patterns = commonPatterns.split(",");
    
    for (const QString &pattern : patterns) {
        if (password.toLower().contains(pattern)) {
            return true;
        }
    }
    
    return false;
}

bool PasswordHash::hasRepeatingCharacters(const QString &password)
{
    for (int i = 0; i < password.length() - 2; ++i) {
        if (password.at(i) == password.at(i + 1) && password.at(i) == password.at(i + 2)) {
            return true;
        }
    }
    return false;
}

bool PasswordHash::hasSequentialCharacters(const QString &password)
{
    for (int i = 0; i < password.length() - 2; ++i) {
        QChar c1 = password.at(i);
        QChar c2 = password.at(i + 1);
        QChar c3 = password.at(i + 2);
        
        if (c1.isLetter() && c2.isLetter() && c3.isLetter()) {
            if (c2.unicode() == c1.unicode() + 1 && c3.unicode() == c2.unicode() + 1) {
                return true;
            }
        }
        
        if (c1.isDigit() && c2.isDigit() && c3.isDigit()) {
            if (c2.unicode() == c1.unicode() + 1 && c3.unicode() == c2.unicode() + 1) {
                return true;
            }
        }
    }
    return false;
}

QString PasswordHash::getUppercaseChars()
{
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

QString PasswordHash::getLowercaseChars()
{
    return "abcdefghijklmnopqrstuvwxyz";
}

QString PasswordHash::getNumberChars()
{
    return "0123456789";
}

QString PasswordHash::getSpecialChars()
{
    return "!@#$%^&*()_+-=[]{}|;:,.<>?";
}

QString PasswordHash::getVowelChars()
{
    return "aeiouAEIOU";
}

QString PasswordHash::getConsonantChars()
{
    return "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
}
