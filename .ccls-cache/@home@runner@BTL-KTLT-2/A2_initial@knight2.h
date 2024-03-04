#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

bool isPaladin(int HP){
  if (HP < 2) return false;
  int cnt = 0;
  for (int i = 1; i <= HP; i++){
    if (HP % i == 0) cnt++;
  }
  if (cnt == 2) return true;
  else return false;
}

bool isLancelot(int HP){
  if (HP == 888) return true;
  else return false;
}

bool isDragonKnight(int HP){
  if (HP < 100 || HP > 999) return false;
  int a = HP % 10, b = (HP / 10) % 10, c = HP / 100;
  if (a*a == b*b + c*c || b*b == a*a + c*c || c*c == a*a + b*b) return true;
  else return false;
}

bool isNormalKnight(int HP){
  if (isPaladin(HP) || isLancelot(HP) || isDragonKnight(HP)) return false;
  return true;
}

class BaseItem;
class BaseBag;
class BaseKnight;
class Events;
class ArmyKnights;
class KnightAdventure;


enum ItemType {/* TODO: */};

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent{
  
};

class MadBear : public BaseOpponent{

};

class Bandit : public BaseOpponent{

};

class LordLupin : public BaseOpponent{

};

class Elf : public BaseOpponent{

};

class Troll : public BaseOpponent{

};

class Tornbery : public BaseOpponent{

};

class QueenOfCards : public BaseOpponent{

};

class NinaDeRings : public BaseOpponent{

};

class DurianGarden : public BaseOpponent{

};

class OmegaWeapon : public BaseOpponent{

};

class Hades : public BaseOpponent{

};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class PaladinKnight : public BaseKnight{
  
};

class LancelotKnight : public BaseKnight{

};

class DragonKnight : public BaseKnight{

};

class NormalKnight : public BaseKnight{

};

class Events {
public:
    Events(const string & file_events){
      
    }
    int count() const;
    int get(int i) const;
};

class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote : public BaseItem{

};

class PhoenixDownI : public BaseItem{

};

class PhoenixDownII : public BaseItem{

};

class PhoenixDownIII : public BaseItem{

};

class PhoenixDownIIII : public BaseItem{

};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};



#endif // __KNIGHT2_H__