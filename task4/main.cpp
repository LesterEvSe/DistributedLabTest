#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <memory>

int main() {
    // Запуск скрипта Python с активацией виртуальной среды
    FILE* pipe = popen("venv/bin/python main.py", "r");
    if (!pipe) {
        std::cerr << "Ошибка при запуске скрипта Python" << std::endl;
        return 1;
    }

    // Отправка URL ввода в Python
    std::string url = "https://ru.wikipedia.org/wiki/%D0%93%D0%BB%D0%B0%D0%B2%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0";
    fprintf(pipe, "%s\n", url.c_str());
    fflush(pipe);

    // Получение результата от Python
    std::vector<std::string> internal_links;
    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        internal_links.emplace_back(buffer);

    // Вывод результатов
    std::cout << "Internal links count: " << internal_links.size() << "\n\n";
    /*
    for (const auto& link : internal_links) {
        std::cout << link;
    }
    */

    // Закрытие потока
    pclose(pipe);

    return 0;
}
