#include <iostream>
#include <string>

using namespace std;


// ___ Implementação: Equipment ___
class Equipment{
    protected:
        string name;
        double exdamage;
        double exdefense;
        double resistance;
        double weight;
    
    public:
    Equipment(string name, double exdamage, double exdefense, double resistance, double weight)
        : name(name), exdamage(exdamage), exdefense(exdefense), resistance(resistance), weight(weight){}

    const string& getName(){ 
        return name; 
    }
    const double getExdamage(){ 
        return exdamage; 
    }
    const double getResistence(){ 
        return resistance; 
    }

    void deterioration(double deterioration_up) {
        resistance -= deterioration_up;
        if (resistance < 0) resistance = 0;
    }

    void toFix(double fix_up) {
        resistance += fix_up;
    }

    bool status(){ 
        return resistance > 0;
    }


};

// ___ Implementação: long_range ___
class long_range : public Equipment{
    protected:
        double range;
        int cargo;

    public:
        long_range(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : Equipment(name, exdamage, exdefense, resistance, weight), range(range), cargo(cargo) {}

        const double getRange(){ 
            return range; 
        }
        const int getCargo(){ 
            return cargo; 
        }

        void recharge(int cargo){
            this->cargo += cargo;
        }

        void upRange(double range){
            this->range += range;
        }
        
};

// ___ Implementação: long_range Waepons ___




// ___ Implementação: Player ___
class Player{
    protected:
        string name;
        double life;
        double baseDamage;
        double resistance;
        //Equipment* PrimaryWeapon;
        //Equipment* SecondaryWeapon;
        //Amor* armor;

    public:
        Player(string name, double life, double baseDamage, double resistance, 
                  string name_dweapon, double exdefense, double dweaponresistence, 
                  string name_oweapon, double exdamage, double oweaponresistence)
                : name(name), life(life), baseDamage(baseDamage), resistance(resistance)// ,  aweapon(name_oweapon, exdamage, oweaponresistence), dweapon(name_dweapon, exdefense, dweaponresistence) 
        {}

        ~Player(){}

        const string& getnam (){ 
            return name; 
        }
        const double getlife(){
            return life; 
        }
        const double getBaseDamage(){
            return baseDamage; 
        }
        const double getresistance(){
            return resistance;
        }

        //OffensiveWeapon getoweapon() { return aweapon; }
        //DefenseWeapon getdweapon() { return dweapon; }

        void setlife(double newlife) {
            life += newlife;
            if (life < 0) life = 0;
        }

        void setdamage(double newdamage){ 
            baseDamage = newdamage; 
        }
        void setresistance(double newresistance){
            resistance = newresistance; 
        }


        bool state(){
            return life > 0; 
        }

        virtual double defense(double damage_sustained) {
            damage_sustained -= resistance;
            if(damage_sustained < 0 ) return 0;
            return damage_sustained;
        }

        virtual double attack(Player& target) {
            double actual_damage = target.defense(baseDamage);
            target.setlife(-actual_damage);
            return actual_damage;
        }
};