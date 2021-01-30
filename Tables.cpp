#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

void generateFile(const string file_name,
                  int width,
                  int height
                  );

int main() {
    int width = 6;
    int height = 4;
    int number_of_files = 1;
    
    cout << "Сколько файлов надо сгенерировать? ";
    cin >> number_of_files;
    
    srand(time(nullptr));
    
    for (int i = 0; i < number_of_files; i++) {
        generateFile("table_" + to_string(i+1) + ".html",
                     width,
                     height);
    }
    
    return 0;
}

void generateFile(const string file_name,
                  int width,
                  int height
                  )
{
    const int total = width * height;
    
    int numbers[total];
    for (int i = 0; i < total; i++) {
        numbers[i] = i + 1;
    }
    
    for (int i = 0; i < total; i++) {
        int j = total;
        while (j >= total) {
            j = rand() /
                ( (RAND_MAX + 1u) / total );
        }
        if (i != j) {
            swap(numbers[i], numbers[j]);
        }
    }
    
    const string style =
        "table {"
            "margin: auto;"
            "margin-top: 10%;"
            "text-align: center;"
        "}"
        "td {"
            "font-size: 40px;"
            "font-weight: bold;"
            "font-family: monospace;"
            "width: 120px;"
            "vertical-align: middle;"
            "padding-top: 20px;"
            "padding-bottom: 20px;"
        "}"
        "table, th, td {"
            "border: 2px solid black;"
            "border-collapse: collapse;"
        "}"
    ;
    
    string table = "<table>";
    for (int i = 0; i < height; i++) {
        table += "<tr>";
        for (int j = 0; j < width; j++) {
            table +=
                "<td>"
                    + to_string(numbers[j + width * i]) +
                "</td>";
        }
        table += "</tr>";
    }
    table += "</table>";
    
    ofstream output;
    output.open(file_name);
    
    output <<
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
            "<style>"
                + style +
            "</style>"
        "<head>"
        "<body>"
            + table +
        "</body>"
        "</html>"
    ;
    
    output.close();
    return;
}
