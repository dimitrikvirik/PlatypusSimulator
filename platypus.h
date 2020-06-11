#pragma once

//ბიბლიოთეკები
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <math.h>
#include <fstream>
//კონსოლის ფერები

//!ყურადღებით ზოგიერთ კომპილერში ეს შეიძლება არ იმუშაოს!//

//გატესტიური Visual Studio 2019-ში//
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//კლასი
class platypus
{
private:
	float weight; //წონა
	short age; // ასაკი თვებში
	std::string name; //სახელი
	char gender; //სქესი
	bool alive; //ცოცხალია თუ არა
	bool mutant; //მუტანტია თუ არა
	/*დამატება*/
	bool plusY = false; // იყო თუ არა ერთი წლით მომატებული
	void died() const; //სიკვდილის დაბეჭდვის ფუნქცია
	std::string newName(char gender); //რანდომული სახელის აღება

	/*---*/
public:

	platypus(); //უპარამეტრო კონსტრუქტორი
	platypus(char gender, short age, float weight, std::string name = "getrand"); // პარამეტრიანი კონსტრუქტორი
    //გეთერები
	float getWeight() const;
	short getAge() const;
	std::string getName() const;
	char getGender() const;
	bool getAlive() const;
	bool getMutant() const;
	//სეთერები
	void setWeight(float& weight, std::istream& in = std::cin);
	void setAge(short& age, std::istream& in = std:: cin);
	void setName(std::string& name, std::istream& in = std::cin);
	void setGender(char& gender, std::istream& in = std::cin);
	void setAlive(const bool& alive);
	void setMutant(const bool& mutant);
	//ფუნქციები
	void print(std::ostream & out = std::cout) const ; //დაბეჭდის ფუნქცია
	void age_me(); //ასაკის მომატება
	void eat() ; //ზრდის  წონას 
	platypus hatch(const std::string name = "getrand"); //ქმნის ახალ პლატიპუს
	void fight( platypus& platypus); //შებრძოლების ფუნქცია
	bool skipIt(short  n) const;
};
/*დამატება*/
//ოპერატორების გადატვირთვა
std::ostream& operator<< (std::ostream& out,   const platypus& platypus) ; //დაბეჭდის ფუნქცია. მეორე ვარიანტი
std::istream& operator>> (std::istream& in,   platypus& pl); //მომხმარებელი თვითონვე შეიყვანს პარამეტრებს
//სხვა ფუნქციები
short randit(short  const&  min , short   const& max); //შემთხვევითი რიცხვის გენერილება
bool chance(short const& pr);  //შანსის გამოთვლა
bool is_number(const std::string& s); //ადგენს თუ სტრინგი შედგება მხოლოდ ციფრებისგან
bool contain_letter(const std::string& s); //ადგენს თუ სტრინგი შეიცავს ასოებს
/*---*/

