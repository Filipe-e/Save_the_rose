#include <iostream>
#include <string>
#include "screensWeapons.hpp"


using namespace std;



// ___ Implementação: Amor ___
class Armor{
    private:
        string name;
        double resistance;
        double weight;
    public:
        const string& getName(){ 
            return name; 
        }
        const double getResistence(){ 
            return resistance; 
        }
        const double getWeight(){ 
            return weight; 
        }

        void deterioration(double deterioration_up) {
            resistance -= deterioration_up;
            if (resistance < 0) resistance = 0;
        }
        bool status_armor(){ 
            return resistance > 0; 
        }

};
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
        const double getExdefense(){ 
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
class LongRange : public Equipment{
    protected:
        double range;
        int cargo;

    public:
        LongRange(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
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

        virtual double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        
};

// ___ Implementação: long_range Waepons ___ 

class Bow : public LongRange{
    private:
        

    public:
        Bow(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : LongRange(name, exdamage, exdefense, resistance, weight, range, cargo){}

        double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        void img(){
            bow();
        }
        
};

class Crossbow : public LongRange{
    private:
        

    public:
        Crossbow(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : LongRange(name, exdamage, exdefense, resistance, weight, range, cargo){}

        double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        void img(){
            crossbow();
        }
        
};


// ___ Implementação: Short_range Waepons ___ 

class Lancer : public Equipment{
    public:
        Lancer(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            slancer();
        }
        
        
};

class SquareShield : public Equipment{
    public:
        SquareShield(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            qshield();
        }
        
        
};

class Shield : public Equipment{
    public:
        Shield(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            vshield();
        }
        
        
};

class LongSword : public Equipment{
    public:
        LongSword(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            sdsword();
        }
        
        
};

class Daggers : public Equipment{
    public:
        Daggers(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            sdaggers();
        }
        
        
};

class SimpleAxe : public Equipment{
    public:
        SimpleAxe(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            oneaxe();
        }
        
        
};

class DoubleAxe : public Equipment{
    public:
        DoubleAxe(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            daxe();
        }
        
        
};

class Hammer : public Equipment{
    public:
        Hammer(string name, double exdamage, double exdefense, double resistance, double weight)
            : Equipment(name, exdamage, exdefense, resistance, weight){}
    
        void img(){
            hammer();
        }
        
        
};
// ___ Implementação: Player ___
class Player{
    protected:
        string name;
        double life;
        double baseDamage;
        double resistance;
        Equipment* PrimaryWeapon;
        Equipment* SecondaryWeapon;
        Armor* armor;

    public:
        Player(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, 
                Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr)
           : name(name), life(life), baseDamage(baseDamage), resistance(resistance), PrimaryWeapon(PrimaryWeapon), SecondaryWeapon(SecondaryWeapon), armor(armor)
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

class Knight : public Player{

    public:
        Knight(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, 
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr) 
            : Player(name, life, baseDamage, resistance, PrimaryWeapon, SecondaryWeapon){}

        bool defesenve_stance() { 
            return (rand() % 3) == 1; 
        }

        double defense(double damage_sustained, int weapon) {
            // try defense
            switch (weapon){
                case 1:
                    if(PrimaryWeapon == nullptr) break;
                    if (PrimaryWeapon->status()) {
                        if (defesenve_stance()) damage_sustained -= (2 * PrimaryWeapon->getExdefense());
                        else damage_sustained -= PrimaryWeapon->getExdefense();
                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;
                case 2:
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        if (defesenve_stance()) damage_sustained -= (2 * SecondaryWeapon->getExdefense());
                        else damage_sustained -= SecondaryWeapon->getExdefense();
                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                case 3:
                    if(PrimaryWeapon != nullptr){
                        if (PrimaryWeapon->status()) {
                            if (defesenve_stance()) damage_sustained -= (2 * PrimaryWeapon->getExdefense());
                            else damage_sustained -= PrimaryWeapon->getExdefense();
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        if (defesenve_stance()) damage_sustained -= (2 * SecondaryWeapon->getExdefense());
                        else damage_sustained -= SecondaryWeapon->getExdefense();
                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                default:
                    break;
            }
            // Armor actions
            if (damage_sustained > 0 && armor->status_armor()) {
                damage_sustained -= armor->getResistence();
                armor->deterioration(armor->getResistence());
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, double damage) {
            if (defesenve_stance()) damage /= 2;
            //if (hero_critical()) damage *= 1.5;
            if (PrimaryWeapon->status()) {
                damage += PrimaryWeapon->getExdamage();
                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};
    // --- Implementação: Muder ---
Muder::Muder(string name, double life, double damage, double resistance, 
             string name_dweapon, double dweaponresistence, 
             string name_oweapon, double exdamage, double oweaponresistence) 
    : Character(name, life, damage, resistance, name_dweapon, (exdamage / 2), dweaponresistence, name_oweapon, exdamage, oweaponresistence) {}

bool Muder::stealthy_posture() { return (rand() % 2) == 0; }

double Muder::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (PrimaryWeapon->status()) {
        actual_damage -= PrimaryWeapon->getExdamage();
        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        size_t chance_of_dodging = 1;
        if (stealthy_posture()) chance_of_dodging = rand() % 2;
        if (actual_damage > 0 && chance_of_dodging != 0) return actual_damage;
    }
    return 0;
}

double Muder::attack(Character& target) {
    double actual_damage = damage;
    if (stealthy_posture()) actual_damage *= 2;
    if (hero_critical()) actual_damage *= 1.5;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}

// --- Implementação: Spearman ---
Spearman::Spearman(string name, double life, double damage, double resistance, 
                   string name_dweapon, double exdefense, double dweaponresistence, 
                   string name_oweapon, double exdamage, double oweaponresistence, 
                   double armor, double armor_resistence, int speed) 
    : Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence), 
      armor(armor), armor_resistence(armor_resistence), speed(speed) {}

bool Spearman::status_armor() { return armor_resistence > 0; }
bool Spearman::provision() { return speed > 1; }
bool Spearman::impulse() { return (rand() % 100) < 30; }

double Spearman::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (PrimaryWeapon->status()) {
        actual_damage -= PrimaryWeapon->getExdamage();
        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
    }
    if (actual_damage > 0 && armor_resistence > 0) {
        actual_damage -= armor;
        armor_resistence -= armor;
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        if (actual_damage > 0) return actual_damage;
    }
    return 0;
}

double Spearman::attack(Character& target) {
    double actual_damage = damage;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    if (provision() && impulse()) {
        actual_damage *= speed;
        speed--;
    }
    if (hero_critical()) actual_damage *= 1.5;
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}

// --- Implementação: Warrior ---
Warrior::Warrior(string name, double life, double damage, double resistance, 
                 string name_dweapon, double exdefense, double dweaponresistence, 
                 string name_oweapon, double exdamage, double oweaponresistence, 
                 double armor, double armor_resistence) 
    : Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence), 
      life_to_berserker(life / 2), armor(armor), armor_resistence(armor_resistence) {}

bool Warrior::status_armor() { return armor_resistence > 0; }
bool Warrior::berserker() { return life < life_to_berserker; }

double Warrior::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (!berserker()) {
        if (PrimaryWeapon->status()) {
            actual_damage -= PrimaryWeapon->getExdamage();
            PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
        }
        if (actual_damage > 0 && armor_resistence > 0) {
            actual_damage -= armor;
            armor_resistence -= armor;
        }
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        if (actual_damage > 0) return actual_damage;
    }
    return 0;
}

double Warrior::attack(Character& target) {
    double actual_damage = damage;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    if (berserker()) actual_damage *= 4;
    if (hero_critical()) actual_damage *= 1.5;
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}