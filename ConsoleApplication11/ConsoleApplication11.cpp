/*Функции:
+ сформировать список студентов / дисциплин
· удалить студента / дисциплину
+ вывести списки студентов с указанием выбранной ими дисциплин
+ определить какая дисциплина выбрана наибольшим количеством студентов */
#include <iostream>
#include <cstring>
using namespace std;

const int N = 9; //Количество студентов
const int M = 9; //Количество дисциплин

struct Disciplines {
    char discipline[80]; // Данные - название дисциплины
    Disciplines* next; // Указатель на следующий элемент списка
    int number_of_students;
};

struct Students {
    char student[80]; // Данные - фамилия студента
    Students* next; // Указатель на следующий элемент списка
    char discipline[80]; // Указатель на выбранную дисциплину
};

void add_students(Students*& start, const char x[], Disciplines*& start_d);
void print_students(const Students* start);
void add_disciplines(Disciplines*& start_d, const char x[]);
char* random_disciplines(const Disciplines* start_d, const int k); // Функция получает рандомное число - номер дисциплины на вход
char* most_popular(const Disciplines* start_d);

int main()
{
    Students* start = NULL;
    Disciplines* start_d = NULL;
    char input[80];
    cout << "Input disciplines: \n";
    for (int i = 0; i < M; ++i) {
        cin.getline(input, 80);
        add_disciplines(start_d, input);
    }
    cout << "Input students: \n";
    for (int i = 0; i < N; ++i) {
        cin.getline(input, 80);
        add_students(start, input, start_d);
    }

    print_students(start);

    cout << "The most popular discipline - " << most_popular(start_d);
}

// Добавление нового элемента в конец списка студентов
void add_students(Students*& start, const char x[], Disciplines*& start_d) {
    srand(time(NULL));
    Students* new_student = new Students; // Адрес нового элемента
    Students* temp; // Для прохода по списку
    char* k = random_disciplines(start_d, rand() % M);
    for (int i = 0; i < 80; ++i) {
        new_student->student[i] = x[i]; // Присвоение значения новому элементу
        new_student->discipline[i] = k[i];
    }
    new_student->next = NULL; // Завершение списка
    if (!start)
        start = new_student; // Формирование нового списка, если список ещё пуст
    else {
        // Проход по списку до последнего элемента
        temp = start;
        while (temp->next)
            temp = temp->next;
        temp->next = new_student; // Ссылка последнего элемента на новый
    }
    return;
}

// Вывод списка студентов
void print_students(const Students* start) {
    if (!start) { //Если список пуст, сообщить об этом
        cout << "Student data not found!";
        return;
    }
    Students* temp = const_cast<Students*>(start); // Для прохода по списку
    // Пока в списке есть элементы, выводить их и перемещать указатель
    while (temp) {
        cout << "Student " << temp->student << " chose a discipline " << temp->discipline << endl;
        temp = temp->next;
    }
    return;
}

// Добавление нового элемента в конец списка дисциплин
void add_disciplines(Disciplines*& start_d, const char x[]) {
    Disciplines* new_disciplines = new Disciplines; // Адрес нового элемента
    Disciplines* temp; // Для прохода по списку
    for (int i = 0; i < 80; ++i)
        new_disciplines->discipline[i] = x[i]; // Присвоение значения новому элементу
    new_disciplines->next = NULL; // Завершение списка
    if (!start_d)
        start_d = new_disciplines; // Формирование нового списка, если список ещё пуст
    else {
        // Проход по списку до последнего элемента
        temp = start_d;
        while (temp->next)
            temp = temp->next;
        temp->next = new_disciplines; // Ссылка последнего элемента на новый
    }
    return ;
}

// Получение адреса рандомного элемента
char* random_disciplines(const Disciplines* start_d, const int k) {
    if (!start_d) return NULL; //Если список пуст, вернуть нулевой указатель
    Disciplines* temp = const_cast<Disciplines*>(start_d); // Для прохода по списку
    // Проход по списку до нужного элемента
    for (int i = 0; i < k - 1; ++i) {
        if (temp) { 
            temp = temp->next; 
        }
    }
    temp->number_of_students++;
    return temp->discipline;
}

char* most_popular(const Disciplines* start_d) {
    if (!start_d) return NULL; //Если список пуст, вернуть нулевой указатель
    Disciplines* temp = const_cast<Disciplines*>(start_d); // Для прохода по списку
    int max_students = temp->number_of_students;
    char* max = temp->discipline;
    for (int i = 0; i < M; ++i) {
        if (temp) {
            if (temp->number_of_students > max_students) {
                max_students = temp->number_of_students;
                max = temp->discipline;
            }
            temp = temp->next;
        }
    }
    return max;
}