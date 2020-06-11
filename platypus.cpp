#include "platypus.h"

//რას ვიყენებთ
using std::cout;
using std::iostream;
using std::ostream;
using std::string;
using std::nothrow;
using std::ifstream;
using std::endl;
using std::boolalpha;
using std::istream;

//უპარამეტრო კონსტრუქტორი
platypus::platypus() {
	this->alive = false;
	if(chance(50)){
		this->gender = 'm';
	}
	else {
		this->gender = 'f';
	}
	this->age = randit(0, 9);
	this->weight = randit(20, 900)/100.;
	this->name = newName(this->gender);
	this->mutant = false;
}


//პარამეტრიანი კონსტრუქტორი
platypus::platypus(char gender, short age, float weight, string name) {

	this->alive = true;
	this->gender = gender;
	this->age = age;
	this->weight = weight;
	//თუ სახელი არ იყო შეყვანილი ან მომხმარებელმა მოითხოვა შემთხვევითი
	if (name == "getrand")
		this->name = newName(this->gender);
	else
		this->name = name;
	this->mutant = new(nothrow) bool(false);
};

//სიკვდილის დაბეჭდვის ფუნქცია
void platypus::died() const {
	cout << BOLDYELLOW << "[INFO]: Platypus " << this->name << " is died!!!\n" << RESET;
}
//ადგენს თუ არის სტრინგი ციფრებისგან
bool is_number(const string& s)
{
	bool dotused = false; //თუ წერტილი უკვე იყო ნახმარი
	for (int  i = 0; i < s.size(); i++) {
		if (i > 1) {
			if(int(s.at(i--)) == int('.')){
				dotused = true;
			
			}
			i++;
		}
		if (!(int(s[i]) >= int('0') && int(s[i]) <= int('9') || int(s[i]) == int('.') && !dotused))
			return false;
	
	}
	return true;
}
//ადგენს თუ სტრინგი შედგება ასოებისგან
bool contain_letter(const string& s) {
	for (int i = 0; i < s.size(); i++) {
		if(int(s[i]) < int('A') || int(s[i]) > int('Z'))
		if (int(s[i]) < int('a') || int(s[i]) > int('z'))
			return false;
	}
	return true;
}

//სახელის მიცემის ფუნქცია
string platypus::newName(const char gender){
	ifstream* ifs1 = new ifstream;
	ifstream* ifs2 = new ifstream;
	if (gender == 'm') {
		//მივაჭინოთ ბიჭის სახელი
		 ifs1->open("boysnames.txt"); //ვიღებთ სიტყვებს ფაილიდან
		 ifs2->open("boysnames.txt");
	}
	else {
		ifs1->open("girlsnames.txt"); //ვიღებთ სიტყვებს ფაილიდან
		ifs2->open("girlsnames.txt");
	}
	short* n = new short;
	*n = 0; 	//სიტყვების რაოდენობა
	string* name = new string;

	//ვადგენთ სიტყვების რაოდენობას.
	while (*ifs1 >> *name) {
		*n += 1;
	}
	delete ifs1;
	string* names = new string[*n ];
	*n = 0;
	//ვაგდებთ მასივში სიტყვებს
	while (*ifs2 >> *name) {
		*(names + *n) = *name;
		*n += 1;
	}
	delete ifs2;
    *n = randit(0, *n -1 );
   return *(names + *n); //დავაბრუნდოთ შემთხვევითი სიტყვა 
}

//დაბეჭდვის ფუნქცია
void platypus::print(ostream & out) const{

	out << BLUE "***Platypus INFO***\n" << RESET << endl 
		<< "   name is: " << this->name << endl
		<< "   Gender is: " << this->gender << endl
		<< "   weight is: " << this->weight << " kg" << endl
		<< "   age is: " << this->age << " months" << endl
		<< "   alive: " << boolalpha << this->alive << endl
		<< "   mutant: " << this->mutant << endl << endl
		<< BLUE << "***End INFO***" << endl << endl << RESET;
}
//დაბეჭდის ფუნქცია ოპერატორის გადატვირთვით
 ostream& operator<< (ostream& out,  const platypus& platypus) {
	 platypus.print(out);
	 return out;
}
 //პარამეტრების შეყვანის ფუნქცია
 istream& operator>> (istream& in, platypus& pl) {


	 char * gender = new char;
	 short* age = new short;
	 float* weight = new float;
	 string* name = new  string("M");
	 bool* check = new bool[4];
	 for (int i = 0; i < 4; i++) {
		 *(check + i) = true;
	 }
	 cout << RED << "***Creating New Platypus***\n\n" << RESET;
	 //შესამოწმებელი მასივი
	 while (true) {
		 //სქესის შეყვანა
		 if (*check) {	
			 pl.setGender(*gender, in);
			 if (*gender == pl.getGender()) {
				 *check = false;
			 }
			 else {
				 continue;
			 }
		 }
		 //ასაკის შეყვანა
		 if(*(check + 1)){
	
			 pl.setAge(*age);
			 if (*age == pl.getAge()) {
				 *(check + 1) = false;
			 }
			 else {
				 continue;
			 }
		 }
		 //წონის შეყვანა
		 if (*(check + 2)) {
			
			 pl.setWeight(*weight);
			 if (*weight == pl.getWeight()) {
				 *(check + 2) = false;
			 }
			 else {
				 continue;
			 }
		 }
		 //სახელის შეყვანა
		 if (*(check + 3)) {
			 pl.setName(*name);
			 if (*name == pl.getName() || *name == "getrand") {
				 *(check + 2) = false;
			 }
			 else {
				 continue;
			 }
		 }
		     //თუ ოთხივე შეყვანა იყო სწორი. მაშინ ლუპიდან გამოვიდეს
			 if (!(*(check) && *(check + 1) && *(check + 2) && *(check + 3)) ) {
				 cout << RED << "***Platypus has created!***\n\n" << RESET;
				 break;
			 }
	 }
	 pl.setAlive(true);
	 delete[] check;
	 delete gender;
	 delete age;
	 delete weight;
	 delete name; 
	 return in;
 }
//შემთხვევითი რიცხვის გამოსათველი ფუნქცია
 short randit(short const & min, short  const  & max) {
	 return  min + (rand() % (max - min + 1));
}
//შანსის დამთხვევის ბულ ფუნქცია
 bool chance(short const& pr) {
	 return pr > randit(0, 100);
}
//თუ რიცხვი მთელია
 bool isInt(double const& n) {
	 if (round(n) == n)
		 return true;
	 else
		 return false;
 }
//ასაკის მომატების ფუნქცია
 void platypus::age_me() {
	 const int mutant_prop = 2;
	 //თუ ცოცხალია
	 if (this->alive) {
		 //ვამოწმებთ თუ ნაჭამია
		 if (this->age < this->weight * 12) {
			 this->age += 1;
			 cout << YELLOW << "[INFO]: +1 Month! " << RESET << endl;
			 if (this->age % 12 == 0) {
				 plusY = true;
			 }
			
			 if (plusY) {
				 //2% შანსია რომ გახდეს მუტანი
				 if (chance(mutant_prop) && this->mutant == false) {
					 cout << BOLDYELLOW << "[INFO]: Platypus " << name <<  " now is Mutant! " << RESET << endl;
					 this->mutant = true;
				 }
				 else {
					 plusY = false;
				 }
			   
				 if (chance(this->weight * 10) == true) {
					 this->alive = false;
				 }
				
			 }
		 }
		 else {
			 cout << BOLDYELLOW <<  "[ALERT]: You must eat your platypus!\n" << RESET;
		 }
	 }
	 else {
		 died();
	 }

 }
 //ზრდის  წონას 
 void platypus::eat() {
	 //თუ ცოცხალია
	 if (this->alive) {
		 float* weight = new float;
		 *weight = this->weight + this->weight / (100 / (randit(10, 500) / 100.));
		 cout << YELLOW << "[INFO]: Eated! " << RESET << endl;
		 this->weight = *weight;
		 delete weight;
	 }
	 else {
		 died();
	 }

	
 }
 //შვილის დაბადება
 platypus platypus::hatch(string name) {
	 //თუ ცოცხალია
	 if (this->alive) {
		 if (age < 12) {
			 cout << BOLDBLUE << "[INFO]" << getName() << " Too Young to have hatch! Min He/She Must be 12 Month! " << endl;
			 platypus pl;
			
			 return pl;
		 }
		 else {
			 char gender;
			 //შემთხვევით სქეს ვაძლევთ 
			 if (chance(50)) {
				 gender = 'm';
			 }
			 else {
				 gender = 'f';
			 }
			 //ვაბრუნებთ შვილს
			 return platypus(gender, 0, randit(1, 10) / 10., name);
		 }
	 }
	 //თუ მშობელი მკვდარია
	 else {
		 cout << BOLDBLUE << "[INFO]: Platypus " << this->name << " can't have child, because he/she died!!!\n" << RESET;
		 platypus pl;
	
		 return pl;
	 }
 }

 //ორი პლატიპის შხუბის ფუნქცია
 void platypus::fight(platypus & fighter)  {
	 //თუ ორივე ცოცხალია
	 if (fighter.alive && this->alive && fighter.age > 12 && this->age > 12) {
		 if ((this->weight / fighter.weight) * 50 > randit(1, 100)) {
			 died();
			 	 setAlive(false);
			 cout << BOLDBLUE << "[INFO]: We have winner: \n " <<  RESET << fighter << endl;
		
		 }
		 else {
			 fighter.setAlive(false);
			 fighter.died();
			 cout << BOLDBLUE << "[INFO]: We have winner: \n " << RESET <<  *this << endl;
		 }
	 }
	 //თუ ერთ-ერთი მკვდარია
	 else if (fighter.age < 12 || this->age < 12) {
		 if (fighter.age < 12) {
	  	 cout << BOLDBLUE << "[INFO]: " << fighter.getName() << " Too Young! Min He/She Must be 12 Months! " << endl;
		 }
		 else {
			 cout << BOLDBLUE << "[INFO]" << getName() << " Too Young! Min He/She Must be 12 Months! " << endl;
		 }
	 }
	 else {
		 if (!(fighter.alive)) {
			 fighter.died();
		 }
		 else {
			 died();
		 }
	 }
 }
 //გეთერები
 float platypus::getWeight()const{
	 return weight;
 }
 short platypus::getAge()const {
	 return age;
 }
 string platypus::getName()const {
	 return name;
 }
 char platypus::getGender()const {
	 return gender;
 }
 bool platypus::getAlive()const {
	 return alive;
 }
 bool platypus::getMutant()const {
	 return mutant;
 }
//სეთერები
 void platypus::setWeight(float& weight, istream& in) {
	 cout << MAGENTA << "Enter weight betwen 0-10: \n" << RESET;
	 string* ch2 = new string;
	 in >> *ch2;
	 //თუ შედგება ციფრებისგან სტრინგი გადავიყვანოთ რიცვებში
	 if (is_number(*ch2))
		 weight = stof(*ch2);
	 else {
		 cout << BOLDRED << "[ERROR]: Non correct input! \n" << RESET;
		 return;
	 }
	 delete ch2;
	 //ვამოწმებთ წონის დიაპაზონს
	 if (weight > 0 && weight < 10)
		 this->weight = weight;
	 else
		 cout << BOLDYELLOW << "[ALERT]: You must set weight  in 0-10 kg diapason!\n" << RESET;
 }
 void  platypus::setAge( short& age, istream& in) {
	 cout << MAGENTA << "Enter age betwen 0-120 months: \n" << RESET;
	 string* ch1 = new string;
	 in >> *ch1;
	 //თუ შედგება ციფრებისგან სტრინგი გადავიყვანოთ რიცვებში
	 if (is_number(*ch1))
		 age = stoi(*ch1);
	 else {
		 cout << BOLDRED << "[ERROR]: Non correct input! \n" << RESET;
		 return;
	 }
	 delete ch1;
	 if (age > 0 && age < 120)
		 this->age = age;
	 else
		 cout << BOLDYELLOW <<  "[ALERT]: You must set age  in 0-120 months diapason!\n" << RESET;
 }
 void  platypus::setName(string& name, istream& in) {
	 cout << MAGENTA << "Enter name or if you want random name input getrand: \n" << RESET;
	 in >> name;
	 //ვამოწმებთ თუ სახელი გრძელია
	 if (!contain_letter(name)) {
		 return;
	 }
	 if (name.size() <= 12) {
		 if (name == "getrand")
			 this->name = newName(this->gender);
		 else
		 this->name = name;
	 }
	 else
		 cout << BOLDYELLOW << "[ALERT]: Too long name! Max lenght is 12 letter! \n" << RESET;
 }
 void  platypus::setGender(char& gender, istream& in) {
	 cout << MAGENTA << "Enter gender: \n" << RESET;
	 string* ch = new string;
	 in >> *ch;
	 //ვამოწმებთ თუ იყო შეყვანილი მხოლოდ ერთი ასო
	 if (ch->size() > 1 && contain_letter(*ch)) {
		 cout << BOLDRED << "[ERROR]: Non correct input!\n" << RESET;
		 return;
	 }
	 else {
		 gender = ch->at(0);
	 }
	 delete ch;
	 if (gender == 'm' || gender == 'f')
		 this->gender = gender;
	 else
		 cout << BOLDYELLOW << "[ALERT]:  You must input m or f!\n" << RESET;
 }
 void  platypus::setAlive(const bool& alive) {
	 this->alive = alive;
 }
 void  platypus::setMutant(const bool& mutant) {
	 this->mutant = mutant;
 }