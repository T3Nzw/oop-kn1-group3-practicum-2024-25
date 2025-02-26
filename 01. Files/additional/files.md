# Файлове

### За работа с файлове ще използваме `<fstream>`.

### Файловите потоци са два вида: входни (`std::ifstream`) и изходни (`std::ofstream`).

| Флаг | Действие |
| ---- | -------- |
| `std::ios::in` | отваря файла за четене |
| `std::ios::out` | отваря файла за писане, като **изтрива** съдържанието му (освен ако не е в комбинация с други определени флагове) |
| `std::ios::binary` | отваря файла в двоичен формат |
| `std::ios::app` | позиционира указателя за писане в края на файла |
| `std::ios::trunc` | изтрива съдържанието на файла, ако съществува | 

*Забележка*: При подаване на повече от един флагове като аргументи се използва побитовият оператор `|` като "разделител" между тях вместо запетаи.

---

| Указател | Извличне на позиция | Модификация на позиция |
| -------- | ------------------- | ---------------------- |
| `get` (четене) | `<входен_поток>.tellg()` | `<входен_поток>.seekg( {<отместване>}, {<позиция>})` |
| `put` (писане) | `<изходен_поток>.tellp()` | `<изходен_поток>.seekp( {<отместване>}, {<позиция>})` |

| Позиция | Описание |
| ------- | -------- |
| `std::ios::beg` | премества указателя с определен брой байтове от началото на файла |
| `std::ios::end` | премества указателя с определен брой байтове от края на файла (използва отрицателно индексиране за изместване назад) |
| `std::ios::cur` | премества указателя с определен брой байтове спрямо текущата му позиция | 

---

| Флаг | Описание на състоянието на потока |
| ---- | --------------------------------- |
| `std::ios::goodbit` | никой от останалите флагове за грешка не е вдигнат |
| `std::ios::eofbit` | достигнат е краят на потока |
| `std::ios::failbit` | възникнала е грешка при входно-изходна операция |
| `std::ios::badbit` | изпълнена е невалидна операция и има загуба на информация |

| Метод | Вдигнат флаг |
| ---------------------------- | ------------ |
| `<поток>.good()` | `std::ios::goodbit` |
| `<поток>.eof()` | `std::ios::eof` |
| `<поток>.bad()` | `std::ios::bad` |
| `<поток>.fail()` | `std::ios::failbit` |

## Други полезни методи на `std::istream`/`std::ostream`

Таблицата **не** съдържа връщаните типове на методите / функциите по-долу с цел прегледност и улеснение. Повечето от методите / функциите връщат референция към самия поток, над който оперират, което позволява верижното им извикване (`std::cout.put('a').put('b').put('c');` ~> `"abc"`). С такива методи ще се занимаваме по-напред в курса.

| Метод / Функция | Поток | Описание | Пример |
| ----- | ----- | -------- | ------ |
| `put(char c)` | `std::ostream` | записва символ `c` в потока | `std::cout.put('a');` |
| `write(char const* s, std::streamsize cnt)` | `std::ostream` | записва `cnt` на брой символа от низа `s` в потока | `std::cout.write("abcd",2);` |
| `operator<<(std::ostream& os, T a)` | `std::ostream` | записва нещо от тип `T` в  потока `os` | `std::cout << 'a'; std::cout << 10;` |
| `get(void)` | `std::istream` | чете 1 символ от потока и го връща като резултат | `char c = std::cin.get();` |
| `getline(char* buf, std::streamsize cnt)` | `std::istream` | чете `cnt-1` символа в `buf` и добавя терминираща нула накрая на низа | `char buf[10]; std::cin(buf,10);` |
| `read(char* buf, std::streamsize cnt)` | `std::istream` | чете `cnt` символа в `buf` | `char buf[10]; std::cin.read(buf,9); buf[9] = '\0';` |
| `get(char& buf)` | `std::istream` | четене 1 символ от потока и го записва в `buf` | `char c; std::cin.get(c);` |
| `operator>>(std::istream& is, T& a)` | `std::istream` | чете `sizeof(T)` байта от потока `is` и ги записва в `a` | `int a; std::cin >> a;` |
| `peek(void)` | `std::istream` | "поглежда" следващия символ в потока, без да го консумира, връща `int` | `std::cin.peek()` |
| `ignore(std::streamsize cnt, int delim)` | `std::istream` | игнорира или `cnt` символа, или спира след първото срещане на `delim` | `std::cin.ignore();` |
| `putback(char c)` | `std::istream` | записва символа `c` в потока, така че следващият прочетен символ да бъде `c` | `std::cout << std::cin.putback('z').get();` |
| `clear(std::base_ios::iostate)` | `std::ostream`/`std::istream` | "изчиства" състоянието на потока | `std::cin.clear();` |

## Текстови файлове

- писане във файл

```c++
//изтрива цялото съдържание на файла. това може да се
//предотврати чрез подаване на std::ios::app
std::ofstream ofile("filename.txt",std::ios::out/*|std::ios::app*/);
//позиционира put указателя в началото на файла.
//ако съдържанието не е било изтрито, би
//презаписало данните в началото на файла
ofile.seekp(0,std::ios::beg);

char const* s = "Some example string";
ofile << s;
ofile << '+' << ' ' << '+';
ofile.put(' ').put('+');  //верижно извикване на метода put
ofile.write("ABCD",2);  //записва само 2 символа в потока

ofile.close();  //затваряне на файла
```

- четене от файл

```c++
std::ifstream ifile("filename.txt",std::ios::in);
ifile.seekg(0,std::ios::beg);

char buf;
//прочита само един символ от входния поток.
//защо не използваме while (ifile) {...}
//или while (!ifile.eof()) {...}?
while (ifile.get(buf)) {
  std::cout << buf;
}

ifile.seekg(0,std::ios::beg);
char buffer[1025];
//прочита цял ред (макс. 1024 символа) 
//от входния поток
while (ifile.getline(buffer,1025)) {
  std::cout << buffer;
}

ifile.seekg(0,std::ios::beg);
char arr[10];
while (ifile.read(arr,10)) {
  
}

ifile.close();
```

## Двоични файлове

#### За отварянето на файл в двоичен режим се използва флагът `std::ios::binary`.

Ще използваме следната примерна структура:

```c++
struct Person {
  char name[32];
  unsigned int age;
};
```

- писане във файл

```c++
std::ofstream ofile("filename.bin",std::ios::out|std::ios::binary);
ofile.seekp(0,std::ios::beg);

Person p1{"Pesho",19};
Person p2{"Gosho",20};

//третираме данните в респективните обекти
//като поредица от байтове (т.к. char е 1 байт)
//и записваме sizeof(Person) на брой байтове във файла
ofile.write((char const*)&p1,sizeof(Person));
ofile.write((char const*)&p2,sizeof(p2));

ofile.close();
```

- четене от файл

```c++
std::ifstream ifile("filename.bin",std::ios::in|std::ios::binary);
ofile.seekp(0,std::ios::beg);

Person p;
//четем последователно sizeof(Person) на брой
//байтове от файла и ги записваме в буфера p
while (ifile.read((char*)&p,sizeof(Person))) {
  std::cout << p.name << ' ' << p.age << std::endl;
}

ifile.close();
```

## Състояние на поток

```c++
//и четирите флага са степени на двойката - защо?
//защо goodbit има стойност 0?
std::cout << "goodbit: " << std::ios::goodbit << '\n';
std::cout << "eofbit: "  << std::ios::eofbit  << '\n';
std::cout << "failbit: " << std::ios::failbit << '\n';
std::cout << "badbit: "  << std::ios::badbit  << '\n';
```

```c++
int buf;
while (true) {
  std::cin >> buff;

  if (std::cin.good()) {
    //ако goodbit е вдигнат, то със сигурност
    //никой от другите флагове не е вдигнат
    std::cout << "goodbit raised\n";
    continue;
  }
  if (std::cin.eof()) {
    std::cout << "eofbit raised\n";
  }
  if (std::cin.fail()) {
    std::cout << "failbit raised\n";
  }
  if (std::cin.bad()) {
    std::cout << "badbit raised\n";
  }

  //изчистваме състоянието на потока
  std::cin.clear();
  //игнорираме оставащите символи в потока,
  //докато не срещнем символ за нов ред
  std::cin.ignore(std::numeric_limist<std::streamsize>::max(),'\n');

  //можем и да използваме само
  //std::cin.ignore();
  //което игнорира само един символ от потока
}
```

```c++
//четене само на валидни int стойности
int buf;
while (true) {
  std::cin >> buf;
  if (!std::cin.good()) {
    std::cout << "reading from input stream failed\n";
    std::cin.clear();
    std::cin.ignore();
  }
  else {
    std::cout << buf << '\n';
  }
}
```