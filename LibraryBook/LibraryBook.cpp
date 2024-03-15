#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

// макрос для пути к файлу
#define FILE_BOOK "D:\\book.txt"

// Структура для хранения информации о книге
struct Book
{
	string title = "";
	string author = "";
	string genre = "";
	int year = 0;
	string status = "";
	vector<double> ratings_book = { 0.0 };
};

// Функция для приведения строки к нижнему регистру 
string BringingStringToLowerCase(string& str)
{
	for_each(str.begin(), str.end(), [](char& c)
		{
			c = ::tolower(static_cast<unsigned char>(c));
		});

	return str;
}

// Функция для замены пробелов
void ReplaceSpacesWithUnderscore(string& str)
{
	replace_if(str.begin(), str.end(), [](char c) { return c == ' '; }, '_');
}

// Функция установки статуса книги
string AvailablityToString()
{
	int status = 0;
	do
	{
		cout << "Enter status book [0.Not available, 1.Availavle] : ";
		cin >> status;
		cout << endl;
	} while (status != 1 && status != 0);

	if (status == 1)
	{
		return "Available";
	}
	else
	{
		return "Not_Available";
	}
}

// Функция для расчета итогового рейтинга
double ComputeRatingsBook(const vector<double>& ratings)
{
	if (ratings.empty())
	{
		return 0;
	}

	double rating_sum = accumulate(ratings.begin(), ratings.end(), 0.0);

	cout << fixed << setprecision(1);
	return rating_sum / static_cast<int>(ratings.size());
}

// Функция ввода рейтинга книги
double ChangingNewRating()
{
	double rating = 0.0;
	do
	{
		cout << "Enter new rating book : ";
		cin >> rating;
		cout << endl;
	} while (rating < 0.0 || rating > 10.0);

	return rating;
}

// Функция для создания оъекта книги
Book AddBook()
{
	cin.ignore();

	string title = "";
	cout << "Enter title : ";
	getline(cin, title);
	ReplaceSpacesWithUnderscore(title);
	cout << endl;

	string author = "";
	cout << "Enter author : ";
	getline(cin, author);
	ReplaceSpacesWithUnderscore(author);
	cout << endl;

	string genre = "";
	cout << "Enter genre : ";
	getline(cin, genre);
	cout << endl;

	int year = 0;
	cout << "Enter year : ";
	cin >> year;
	cout << endl;

	string status = AvailablityToString();

	return { title, author, genre, year, status };
}

// Класс для работы с книгами
class Library
{
public:

	// Метод поиска книги по названию
	void FindTitleBook(string& title, vector<Book>& books)
	{
		for (Book& book : books)
		{
			if (BringingStringToLowerCase(book.title) == BringingStringToLowerCase(title))
			{
				double rating = ComputeRatingsBook(book.ratings_book);
				cout << "---------------------------------------------------" << endl;
				cout << "Title      : " << book.title << endl << "Author     : " << book.author << endl << "Year       : " << book.year << endl << "Genre      : " << book.genre << endl << "Available  : " << book.status << endl << "Rating     : " << rating << endl;
				cout << "---------------------------------------------------" << endl;
			}
		}
	}

	// Метод поска книги по автору
	void FindAuthorBook(string& author, vector<Book>& books)
	{
		for (Book& book : books)
		{
			if (BringingStringToLowerCase(book.author) == BringingStringToLowerCase(author))
			{
				double rating = ComputeRatingsBook(book.ratings_book);
				cout << "---------------------------------------------------" << endl;
				cout << "Title      : " << book.title << endl << "Author     : " << book.author << endl << "Year       : " << book.year << endl << "Genre      : " << book.genre << endl << "Available  : " << book.status << endl << "Rating     : " << rating << endl;
				cout << "---------------------------------------------------" << endl;
			}
		}
	}

	// Метод для поиска книг по жанрам
	void FindGenreBook(string& genre, vector<Book>& books)
	{
		for (Book& book : books)
		{
			if (BringingStringToLowerCase(book.genre) == BringingStringToLowerCase(genre))
			{
				double rating = ComputeRatingsBook(book.ratings_book);
				cout << "---------------------------------------------------" << endl;
				cout << "Title      : " << book.title << endl << "Author     : " << book.author << endl << "Year       : " << book.year << endl << "Genre      : " << book.genre << endl << "Available  : " << book.status << endl << "Rating     : " << rating << endl;
				cout << "---------------------------------------------------" << endl;
			}
		}
	}

	// Метод для удаления книги по названию
	vector<Book> DeleteBook(vector<Book>& books, const string& title)
	{
		books.erase(remove_if(books.begin(), books.end(), [&](const Book& b)
			{ return b.title == title; }), books.end());

		return books;
	}

	// Метод для вывода всех книг
	void ShowBooksInLibrary(vector<Book>& books)
	{
		for (const Book& book : books)
		{
			double rating = ComputeRatingsBook(book.ratings_book);
			cout << "---------------------------------------------------" << endl;
			cout << "Title      : " << book.title << endl << "Author     : " << book.author << endl << "Year       : " << book.year << endl << "Genre      : " << book.genre << endl << "Available  : " << book.status << endl << "Rating     : " << rating << endl;
			cout << "---------------------------------------------------" << endl;
		}
	}

	// Метод для изменения статуса книги
	vector<Book> ChangingStatusBook(const string& title, vector<Book>& books)
	{
		for (auto& book : books)
		{
			if (book.title == title)
			{
				book.status = AvailablityToString();
			}
		}
		return books;
	}

	// метод для изменения рейтинга книги
	vector<Book> ChangingRatingBook(const string& title, vector<Book>& books)
	{
		for (auto& book : books)
		{
			if (book.title == title)
			{
				double rating = ChangingNewRating();
				book.ratings_book.push_back(rating);
				return books;
			}
		}
	}
};

// Класс для работы с файлом
class File
{
public:

	// Метод для записи информации о книгах в файл
	void WriteToFile(vector<Book>& books)
	{
		ofstream file(FILE_BOOK);

		if (file.is_open())
		{
			for (const Book& book : books)
			{
				file << book.title << " " << book.author << " " << book.genre << " " << book.year << " " << book.status << " " << book.ratings_book.size() << " ";
				for (const double rating_vec : book.ratings_book)
				{
					file << rating_vec << " ";
				}
				file << endl;
			}
		}
		else
		{
			throw("File opening error");
		}
		file.close();
	}

	// Метод для получение всех записей о книгах из файла
	vector<Book> GetDataToFile()
	{
		vector<Book> book_vector = {};

		ifstream file(FILE_BOOK);

		if (file.is_open())
		{
			Book book;

			for (int i = 0; i < CountLinesInFile(); i++)
			{
				int size_vector = 0;

				file >> book.title >> book.author >> book.genre >> book.year >> book.status >> size_vector;

				book.ratings_book.resize(size_vector);
				for (double& mark : book.ratings_book)
				{
					file >> mark;
				}
				book_vector.push_back(book);
			}
		}
		else
		{
			throw("Data could not be retrieved from the file!"s);
		}
		return book_vector;
	}

	// Метод для получения количества книг в библиотеке
	int CountLinesInFile()
	{
		int count = 0;
		string line = "";

		ifstream file(FILE_BOOK);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				count++;
			}
		}
		return count;
	}
};

// Функция с основым пользовательским меню
void UserMenu()
{
	Library library;
	File file;
	Book book;

	vector<Book> books = file.GetDataToFile(); // получаем данные из файла

	int user_choice = 0;
	bool yes_no = true;

	do
	{
		system("cls");

		cout << "1.Add new book" << endl;
		cout << "2.Find book by title" << endl;
		cout << "3.Font book by author" << endl;
		cout << "4.Search for books by genre" << endl;
		cout << "5.Delete the book" << endl;
		cout << "6.Changing the status of a book" << endl;
		cout << "7.Add a new rating" << endl;
		cout << "8.Show all the books in the library" << endl;
		cout << "9.Exit" << endl;

		cout << "Select an item : ";
		cin >> user_choice;
		cout << endl;

		system("cls");

		if (user_choice == 1) // добавление книги
		{
			book = AddBook();
			books.push_back(book);

			file.WriteToFile(books);
		}
		if (user_choice == 2) // поиск по названию
		{
			cin.ignore();
			string title = "";
			cout << "Enter the name of the book to search for : ";
			getline(cin, title);
			cout << endl;

			library.FindTitleBook(title, books);
			system("pause");
		}
		if (user_choice == 3) // поиск по автору
		{
			cin.ignore();
			string author = "";
			cout << "Enter the author of the book to search for : ";
			getline(cin, author);
			cout << endl;

			library.FindAuthorBook(author, books);
			system("pause");
		}
		if (user_choice == 4) // поиск по жанру
		{
			cin.ignore();
			string genre = "";
			cout << "Enter the genre of the book to search for : ";
			getline(cin, genre);
			cout << endl;

			library.FindGenreBook(genre, books);
			system("pause");
		}
		if (user_choice == 5) // удаление книги по названию
		{
			cin.ignore();
			string title = "";
			cout << "Enter the title of the book to delete : ";
			getline(cin, title);
			cout << endl;

			books = library.DeleteBook(books, title);
			file.WriteToFile(books);
			system("pause");
		}
		if (user_choice == 6) // изменение статуса книги
		{
			cin.ignore();
			string title = "";
			cout << "Enter the title of the book to change its status : ";
			getline(cin, title);
			cout << endl;

			books = library.ChangingStatusBook(title, books);
			file.WriteToFile(books);
			system("pause");
		}
		if (user_choice == 7) // добавление оценки книги
		{
			cin.ignore();
			string title = "";
			cout << "Enter the title of the book to change its status : ";
			getline(cin, title);
			cout << endl;

			books = library.ChangingRatingBook(title, books);
			file.WriteToFile(books);
			system("pause");
		}

		if (user_choice == 8) // просмотр всех книг
		{
			cout << "Total books in the library : " << file.CountLinesInFile() << endl;
			library.ShowBooksInLibrary(books);
			system("pause");
		}
		if (user_choice == 9) // выход из программы
		{
			yes_no = false;
		}

	} while (yes_no);
}

// Функция для автоматического заполнения файла, если что-то пошло не так
void AutomaticFillingFile()
{
	vector<Book> booksVector = {};

	booksVector.push_back({ "1984", "George_Orwell", "Dystopian", 1949, "Availavle", {8.7, 6.7, 9.8, 7.6, 8.8} });
	booksVector.push_back({ "To_Kill_a_Mockingbird", "Harper_Lee", "Fiction", 1960, "Availavle", {8.8, 7.7, 6.8, 9.3, 5.5} });
	booksVector.push_back({ "The_Great_Gatsby", "F._Scott_Fitzgerald", "Classic", 1925, "Availavle", {8.7, 7.4, 8.6} });
	booksVector.push_back({ "One_Hundred_Years_of_Solitude", "Gabriel_Garcia_Marquez", "Magical_Realism", 1967, "Availavle", {9.6} });
	booksVector.push_back({ "Brave_New_World", "Aldous_Huxley", "Dystopian", 1932, "Availavle", {7.9, 9.5} });
	booksVector.push_back({ "The_Catcher_in_the_Rye", "J.D.Salinger", "Coming_Of_Age", 1951, "Availavle", {8.9} });
	booksVector.push_back({ "The_Lord_of_the_Rings", "J.R.R.Tolkien", "Fantasy", 1954, "Availavle", {9.9, 6.7, 8.9} });
	booksVector.push_back({ "Pride_and_Prejudice", "Jane_Austen", "Romance", 1813, "Availavle", {8.8} });
	booksVector.push_back({ "Crime_and_Punishment", "Fyodor_Dostoevsky", "Psychological_Fiction", 1866, "Availavle", {8.6, 7.8} });
	booksVector.push_back({ "The_Odyssey", "Homer", "Epic", -800, "Availavle", {9.2, 8.7, 6.9} });
	booksVector.push_back({ "War_and_Peace", "Leo_Tolstoy", "Historical_Fiction", 1869, "Availavle", {9.6, 9.1, 8.8} });
	booksVector.push_back({ "Frankenstein", "Mary_Shelley", "Gothic", 1818, "Availavle", {7.8, 8.6, 9.5} });
	booksVector.push_back({ "The_Count_of_Monte_Cristo", "Alexandre_Dumas", "Adventure", 1844, "Availavle", {9.7} });
	booksVector.push_back({ "Moby-Dick", "Herman_Melville", "Adventure", 1851, "Availavle", {8.8, 9.3, 7.9} });
	booksVector.push_back({ "Hamlet", "William_Shakespeare", "Drama", 1603, "Availavle", {9.5, 9.6} });

	File file;
	file.WriteToFile(booksVector);
}

int main()
{
	UserMenu();

	//AutomaticFillingFile();
}

