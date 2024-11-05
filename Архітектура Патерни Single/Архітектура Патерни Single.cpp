#include <iostream>
#include <string>
#include <windows.h>
#include <mutex>
using namespace std;

class Logger {
private:
    // Приватний конструктор, щоб запобігти створенню інших екземплярів
    Logger() = default;

    // Приватний деструктор
    ~Logger() = default;

    // Забороняємо копіювання та присвоєння
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Статичний вказівник на єдиний екземпляр
    static Logger* instance;

    // М'ютекс для забезпечення потокобезпеки
    static mutex mtx;

public:
    // Метод для отримання єдиного екземпляра
    static Logger* getInstance() {
        // Блокування доступу до екземпляра для забезпечення потокобезпеки
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }

    // Метод для запису повідомлень у лог
    void log(const string& message) {
        cout << "Лог: " << message << endl;
    }
};

// Ініціалізація статичних змінних
Logger* Logger::instance = nullptr;
mutex Logger::mtx;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Отримання єдиного екземпляра Logger та запис повідомлень
    Logger::getInstance()->log("Перше повідомлення");
    Logger::getInstance()->log("Друге повідомлення");

}

