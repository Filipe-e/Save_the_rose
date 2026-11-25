#ifndef CLASSES_HPP
#define CLASSES_HPP

//basic includes
#include <iostream>
#include <vector>
#include <string>

//our includes
#include "screensWeapons.hpp"
#include "itens.hpp"

using namespace std;

//base class
class Player{
    protected:
        string name;
        double life;
        double baseDamage;
        double resistance;
        int weight;
        int coins;
        Equipment* PrimaryWeapon;
        Equipment* SecondaryWeapon;
        Armor* armor;
        vector<Itens>* itens; 

    public:
        Player(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, int coins, 
                Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr)
           : name(name), life(life), baseDamage(baseDamage), resistance(resistance), weight(weight), coins(coins), PrimaryWeapon(PrimaryWeapon), SecondaryWeapon(SecondaryWeapon), armor(armor)
        {}

        ~Player(){}

        const string& getname(){ 
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
        const Equipment getPrimaryWeapon(){
            return *PrimaryWeapon;
        }
        const Equipment getSecondaryWeapon(){
            return *SecondaryWeapon;
        }
        const Armor getArmor(){
            return *armor;
        }
        vector<Itens>* getIten(){
            return itens;
        }

        virtual void setlife(double newlife) {
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

//specialized classes
class Archer : public Player{
    private: 
        bool doubleShoot;

    public:
        Archer(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, int coins,
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor){}

        const double getRange(){
            if(PrimaryWeapon && PrimaryWeapon->getName().find("Bow") != string::npos) return PrimaryWeapon->getRange()*1.5;
            if(SecondaryWeapon && SecondaryWeapon->getName().find("Bow") != string::npos) return SecondaryWeapon->getRange()*1.5;
            if(PrimaryWeapon && PrimaryWeapon->getName().find("Crossbow") != string::npos) return PrimaryWeapon->getRange()*1.5;
            if(SecondaryWeapon && SecondaryWeapon->getName().find("Crossbow") != string::npos) return SecondaryWeapon->getRange()*1.5;
            return 0;
        }

        bool doubleShootting() { 
            return (rand() % 3) == 1; 
        }

        void try_doubleShootting(bool upoff){ 
            doubleShoot = upoff;
        }
        
        double defense(double damage_sustained, int weapon) {
            //try defense
            switch (weapon){
                //defende com a primaria
                case 1:
                    //verifica existencia de arma
                    if(PrimaryWeapon == nullptr) break;

                    //verifica se a arma ainda tem resistencia
                    if (PrimaryWeapon->status()) {
                        damage_sustained -= PrimaryWeapon->getExdefense();

                        //verifica maestria de armas
                        if(PrimaryWeapon->getName().find("Bow") != string::npos){ 
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                            break;
                        }else{
                            if(PrimaryWeapon->getName().find("Crossbow") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                                break;
                            }
                        }
                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;

                //defende com a secundaria
                case 2:
                    //verifica existencia de arma
                    if(SecondaryWeapon == nullptr) break;

                    //verifica se a arma ainda tem resistencia
                    if (SecondaryWeapon->status()) {
                        //verifica pose defensiva
                        damage_sustained -= SecondaryWeapon->getExdefense();

                        //verifica maestria de armas
                        if(SecondaryWeapon->getName().find("Bow") != string::npos){ 
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                            break;
                        }else{
                            if(SecondaryWeapon->getName().find("Crossbow") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                        }
                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                     
                    }
                    break;

                //defende com as duas armas
                case 3:
                    //verifica existencia de arma
                    if(PrimaryWeapon != nullptr){
                    
                        //verifica se a arma ainda tem resistencia
                        if (PrimaryWeapon->status()) {
                            //verifica pose defensiva
                            damage_sustained -= PrimaryWeapon->getExdefense();
                            
                            //verifica maestria de armas
                            if(PrimaryWeapon->getName().find("Bow") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);    
                            }else{
                                if(PrimaryWeapon->getName().find("Crossbow") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);    
                                }else{
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                }
                            }
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        damage_sustained -= SecondaryWeapon->getExdefense();
                        if(SecondaryWeapon->getName().find("Bow") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Crossbow") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;

                default:
                    break;
            }
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()); 
                            if(PrimaryWeapon->getName().find("Bow") != string::npos && doubleShoot){ 
                                damage += PrimaryWeapon->shoot();
                                break;
                            }
                            else{
                                if(PrimaryWeapon->getName().find("Crossbow") != string::npos){ 
                                    damage += PrimaryWeapon->shoot();
                                    break;
                                }
                            }
                            damage += PrimaryWeapon->getExdamage();
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()); 
                            if(SecondaryWeapon->getName().find("Bow") != string::npos){ 
                                damage += SecondaryWeapon->shoot();
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Crossbow") != string::npos){ 
                                    damage += SecondaryWeapon->shoot();
                                    break;
                                }
                            }
                            damage += PrimaryWeapon->getExdamage();
                        }
                        break;
                    case 3:
                        if(PrimaryWeapon == nullptr){
                            if (PrimaryWeapon->status()) {
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                if(PrimaryWeapon->getName().find("Bow") != string::npos){ 
                                    damage += PrimaryWeapon->shoot();
                                }
                                else{
                                    if(PrimaryWeapon->getName().find("Crossbow") != string::npos){ 
                                        damage += PrimaryWeapon->shoot();
                                        
                                    }
                                    else{
                                        damage += PrimaryWeapon->getExdamage();
                                    }
                                }
                            }
                        }
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                            if(SecondaryWeapon->getName().find("Bow") != string::npos){ 
                                damage += SecondaryWeapon->shoot();
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Crossbow") != string::npos){ 
                                    damage += SecondaryWeapon->shoot();
                                    break;
                                }
                            }
                            damage += SecondaryWeapon->getExdamage();
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};

class Knight : public Player{
    private:
        bool defesenveStance;

    public:
        Knight(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, int coins,
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor){}

        bool defesenve_stance() { 
            return (rand() % 3) == 1; 
        }
        void turn_defesenve_stance(bool upoff){ 
            defesenveStance = upoff;
        }

        double defense(double damage_sustained, int weapon) {
            //try defense
            switch (weapon){
                //defende com a primaria
                case 1:
                    //verifica existencia de arma
                    if(PrimaryWeapon == nullptr) break;

                    //verifica se a arma ainda tem resistencia
                    if (PrimaryWeapon->status()) {
                        //verifica pose defensiva
                        if(defesenveStance && defesenve_stance()) damage_sustained -= (2 * PrimaryWeapon->getExdefense());
                        else damage_sustained -= PrimaryWeapon->getExdefense();

                        //verifica maestria de armas
                        if(PrimaryWeapon->getName().find("Sword") != string::npos){ 
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                            break;
                        }else{
                            if(PrimaryWeapon->getName().find("Shield") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                                break;
                            }
                        }
                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;

                //defende com a secundaria
                case 2:
                    //verifica existencia de arma
                    if(SecondaryWeapon == nullptr) break;

                    //verifica se a arma ainda tem resistencia
                    if (SecondaryWeapon->status()) {
                        //verifica pose defensiva
                        if(defesenveStance && defesenve_stance()) damage_sustained -= (2 * SecondaryWeapon->getExdefense());
                        else damage_sustained -= SecondaryWeapon->getExdefense();

                        //verifica maestria de armas
                        if(SecondaryWeapon->getName().find("Sword") != string::npos){ 
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                            break;
                        }else{
                            if(SecondaryWeapon->getName().find("Shield") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                        }
                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                     
                    }
                    break;

                //defende com as duas armas
                case 3:
                    //verifica existencia de arma
                    if(PrimaryWeapon != nullptr){
                    
                    //verifica se a arma ainda tem resistencia
                    if (PrimaryWeapon->status()) {
                        //verifica pose defensiva
                        if(defesenveStance && defesenve_stance()) damage_sustained -= (2 * PrimaryWeapon->getExdefense());
                        else damage_sustained -= PrimaryWeapon->getExdefense();
                        
                        //verifica maestria de armas
                        if(PrimaryWeapon->getName().find("Sword") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    
                                }
                                else{
                                    if(PrimaryWeapon->getName().find("Shield") != string::npos){ 
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                        
                                    }
                                    else{
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                    }
                                }
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        if(defesenveStance && defesenve_stance()) damage_sustained -= (2 * SecondaryWeapon->getExdefense());
                        else damage_sustained -= SecondaryWeapon->getExdefense();
                        if(SecondaryWeapon->getName().find("Sword") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Shield") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                default:
                    break;
            }
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage += PrimaryWeapon->getExdamage(); 
                            if(defesenveStance){
                                if (defesenve_stance()) damage /= 2;
                            }
                            if(PrimaryWeapon->getName().find("Sword") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(PrimaryWeapon->getName().find("Shield") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                     
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            if(defesenveStance){
                                if (defesenve_stance()) damage /= 2;
                            }
                            if(SecondaryWeapon->getName().find("Sword") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Shield") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                     
                        }
                        break;
                    case 3:
                        if(PrimaryWeapon == nullptr){
                            if (PrimaryWeapon->status()) {
                                damage += PrimaryWeapon->getExdamage(); 
                                if(defesenveStance){
                                    if (defesenve_stance()) damage /= 2;
                                }
                                if(PrimaryWeapon->getName().find("Sword") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    
                                }
                                else{
                                    if(PrimaryWeapon->getName().find("Shield") != string::npos){ 
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                        
                                    }
                                    else{
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                    }
                                }
                            }
                        }
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            if(defesenveStance){
                                if (defesenve_stance()) damage /= 2;
                            }
                            if(SecondaryWeapon->getName().find("Sword") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("Shield") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};

class Murder : public Player{
    private:
        bool furtive;

    public:
        Murder(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, int coins, 
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor){}

        bool defesenve_futive(int w) { 
            return (rand() % w) < 2; 
        }
        void turn_futive(bool upoff){ 
            furtive = upoff;
        }

        double defense(double damage_sustained, int weapon) {
            // try defense
            if(furtive && defesenve_futive(weight)) return 0;
            damage_sustained *= 2;
            switch (weapon){
                case 1:
                    if(PrimaryWeapon == nullptr) break;
                    if (PrimaryWeapon->status()) {
                        damage_sustained -= PrimaryWeapon->getExdefense();
                        if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/1.4);
                                break;
                            }
                            else{
                                if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/1.4);
                                    break;
                                }
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;
                case 2:
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        damage_sustained -= SecondaryWeapon->getExdefense();
                        if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                     
                    }
                    break;
                case 3:
                    if(PrimaryWeapon != nullptr){
                        if (PrimaryWeapon->status()) {
                            damage_sustained -= PrimaryWeapon->getExdefense();
                                if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    
                                }
                                else{
                                    if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                        
                                    }
                                    else{
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                    }
                                }
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        damage_sustained -= SecondaryWeapon->getExdefense();
                        if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                default:
                    break;
            }
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage += PrimaryWeapon->getExdamage(); 
                            if(defesenve_futive(weight) && furtive) damage *= 2;
                            
                            if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                     
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            if(defesenve_futive(weight) && furtive) damage *= 2;
                            if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                     
                        }
                        break;
                    case 3:
                        if(PrimaryWeapon == nullptr){
                            if (PrimaryWeapon->status()) {
                                damage += PrimaryWeapon->getExdamage(); 
                            if(defesenve_futive(weight) && furtive) damage *= 2;
                                if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                    
                                }
                                else{
                                    if(PrimaryWeapon->getName().find("daggers") != string::npos){ 
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                        
                                    }
                                    else{
                                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                    }
                                }
                            }
                        }
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            if(defesenve_futive(weight) && furtive) damage *= 1.2;
                            if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                break;
                            }
                            else{
                                if(SecondaryWeapon->getName().find("daggers") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage()/2);
                                    break;
                                }
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};

class Spearman : public Player{
    private:
        double acceleration;

    public:
        Spearman(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, double acceleration = 1, int coins, 
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor), acceleration(acceleration){}

        double getAcceleration(){
            return acceleration;
        }
            void rest() { 
            acceleration++; 
        }
        double impulse(){ 
            if(acceleration > 0 && (rand() % 3) == 1) return acceleration;
            return 1;
        }

        double defense(double damage_sustained, int weapon) {
            // try defense
            switch (weapon){
                case 1:
                    if(PrimaryWeapon == nullptr) break;
                    if (PrimaryWeapon->status()) {
                        damage_sustained -= PrimaryWeapon->getExdefense();
                        if(PrimaryWeapon->getName().find("lancer") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/1.4);
                                break;
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;
                case 2:
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        damage_sustained -= SecondaryWeapon->getExdefense();
                        if(SecondaryWeapon->getName().find("lancer") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                break;
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                     
                    }
                    break;
                case 3:
                    if(PrimaryWeapon != nullptr){
                        if (PrimaryWeapon->status()) {
                            damage_sustained -= PrimaryWeapon->getExdefense();
                            if(PrimaryWeapon->getName().find("lancer") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                            }
                            else{
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                            }   
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                        if(SecondaryWeapon->status()){
                            damage_sustained -= SecondaryWeapon->getExdefense();
                            if(SecondaryWeapon->getName().find("lancer") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                    break;
                            }
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                default:
                    break;
            }
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage += PrimaryWeapon->getExdamage(); 
                            damage *= impulse();
                            acceleration--;
                            if(acceleration < 1) acceleration = 1;
                            if(PrimaryWeapon->getName().find("lancer") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                                break;
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            damage *= impulse();
                            acceleration--;
                            if(acceleration < 1) acceleration = 1;
                            if(SecondaryWeapon->getName().find("lancer") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};

class Warrior : public Player{
    private:
        double lifeRef;
    public:
        Warrior(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2, int coins, double lifeRef = 1, 
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor), lifeRef(life){}

        void setlife(double newlife) override {
            if(life < (life+newlife)) lifeRef = life+newlife;
            life += newlife;
            if (life < 0) life = 0;
        }
        int berserker(){ 
            if(life < (lifeRef/3)) return 5;
            return 1;
        }

        double defense(double damage_sustained, int weapon) {
            // try defense
            if(berserker() == 1){
                switch (weapon){
                    case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage_sustained -= PrimaryWeapon->getExdefense();
                            if(PrimaryWeapon->getName().find("Axe") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/1.4);
                                    break;
                                }
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage_sustained -= SecondaryWeapon->getExdefense();
                            if(SecondaryWeapon->getName().find("Axe") != string::npos){ 
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                    break;
                                }
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                            
                        }
                        break;
                    case 3:
                        if(PrimaryWeapon != nullptr){
                            if (PrimaryWeapon->status()) {
                                damage_sustained -= PrimaryWeapon->getExdefense();
                                if(PrimaryWeapon->getName().find("Axe") != string::npos){ 
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage()/2);
                                }
                                else{
                                    PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());
                                }   
                            }
                        }
                        if(SecondaryWeapon == nullptr) break;
                            if(SecondaryWeapon->status()){
                                damage_sustained -= SecondaryWeapon->getExdefense();
                                if(SecondaryWeapon->getName().find("Axe") != string::npos){ 
                                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/1.4);
                                        break;
                                }
                                    SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                        }
                        break;
                    default:
                        break;
                }
            }
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage += PrimaryWeapon->getExdamage(); 
                            damage *= berserker();
                            if(PrimaryWeapon->getName().find("Axe") != string::npos){ 
                                PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense()/2);
                                break;
                            }
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            damage *= berserker();
                            if(SecondaryWeapon->getName().find("Axe") != string::npos){ 
                                SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense()/2);
                                break;
                            }
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};

class Cleric : public Player{
    private:
        double faith;
    public:
        Cleric(string name="\0", double life=1.0, double baseDamage=0.0, double resistance=0.0, int weight = 2,  int coins, double faith = 1,
                    Equipment* PrimaryWeapon = nullptr, Equipment* SecondaryWeapon = nullptr, Armor* armor = nullptr) 
            : Player(name, life, baseDamage, resistance, weight, coins, PrimaryWeapon, SecondaryWeapon, armor), faith(faith){}

        void setlife(double newlife) override {
            if(newlife > 0) newlife *= 2;
            life += newlife;
            if (life < 0) life = 0;
        }
        void healing(Player& target, int heal){ 
            target.setlife(heal);
        }

        double defense(double damage_sustained, int weapon) {
            // try defense
            switch (weapon){
                case 1:
                    if(PrimaryWeapon == nullptr) break;
                    if (PrimaryWeapon->status()) {
                        damage_sustained -= PrimaryWeapon->getExdefense();    
                        PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                    }
                    break;
                case 2:
                    if(SecondaryWeapon == nullptr) break;
                    if (SecondaryWeapon->status()) {
                        damage_sustained -= SecondaryWeapon->getExdefense();
                        SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                        
                    }
                    break;
                case 3:
                    if(PrimaryWeapon != nullptr){
                        if (PrimaryWeapon->status()) {
                            damage_sustained -= PrimaryWeapon->getExdefense();
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdamage());   
                        }
                    }
                    if(SecondaryWeapon == nullptr) break;
                        if(SecondaryWeapon->status()){
                            damage_sustained -= SecondaryWeapon->getExdefense();
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdefense());
                    }
                    break;
                default:
                    break;
            }
            
            // Armor actions
            if(armor != nullptr){
                if (damage_sustained > 0 && armor->status_armor()) {
                    damage_sustained -= armor->getResistence();
                    armor->deterioration(armor->getResistence());
                }
            }
            // Base Resistence
            if (damage_sustained > 0) {
                damage_sustained -= resistance;
                if (damage_sustained > 0) return damage_sustained;
            }
            return 0;
        }

        double attack(Player& target, int weapon) {
            double damage = baseDamage;
            
            switch (weapon){
                case 1:
                        if(PrimaryWeapon == nullptr) break;
                        if (PrimaryWeapon->status()) {
                            damage += PrimaryWeapon->getExdamage(); 
                            PrimaryWeapon->deterioration(PrimaryWeapon->getExdefense());
                        }
                        break;
                    case 2:
                        if(SecondaryWeapon == nullptr) break;
                        if (SecondaryWeapon->status()) {
                            damage += SecondaryWeapon->getExdamage(); 
                            SecondaryWeapon->deterioration(SecondaryWeapon->getExdamage());
                        }
                        break;
                    default:
                        break;
            }
            damage = target.defense(damage);
            target.setlife(-damage);
            return damage;
        }
};


#endif