#include <Hallinta.hpp>
#include <memory>
#include <iostream>

class KuvallinenKonsoli : public Hallintarajapinta {
public:
  void piirra() {
    std::cout << "Piirretään kuvallinen konsoli\n";
  }

  ~KuvallinenKonsoli() {
    std::cout << "Tuhotaan kuvallinen konsoli\n";
  }
};

class Partikkelit : public Hallintarajapinta {
public:
  void piirra() {
    std::cout << "Piirretään partikkelit\n";
  }

  void laske() {
    std::cout << "Lasketaan partikkelien sijainnit\n";
  }

  ~Partikkelit() {
    std::cout << "Tuhotaan partikkelit\n";
  }
};

class Alkuvalikko : public Hallintarajapinta {
public:
  void piirra() {
    std::cout << "Piirretään alkuvalikko\n";
  }

  ~Alkuvalikko() {
    std::cout << "Tuhotaan alkuvalikko\n";
  }
};

class Peli{
  Hallinta hallinta;
public:

  void aloita() {
    // luodaan alkuvalikko ja näytetään se
    std::shared_ptr<Alkuvalikko> alkuvalikko {new Alkuvalikko};
    hallinta.lisaaSubjekti(alkuvalikko);
    hallinta.piirraKaikki();
    // alkuvalikko tuhoutuu kun pointerin scope loppuu
  }

  void luuppi(int aikaraja) {
    //luodaan kuvallinen konsoli ja partikkelit, ja aloitetaan niiden hallinta
    std::shared_ptr<KuvallinenKonsoli> konsoli {new KuvallinenKonsoli};
    std::shared_ptr<Partikkelit> partikkelit {new Partikkelit};
    hallinta.lisaaSubjekti(konsoli);
    hallinta.lisaaSubjekti(partikkelit);
    //toistetaan peliluuppia kunnes aikaraja tulee täyteen
    for(int t=0; t<aikaraja; t++) {
      std::cout << "t = " << t << "\n";
      hallinta.laskeKaikki();
      hallinta.piirraKaikki();
    }
  }

};

 int main() {
   Peli P;
   P.aloita();
   P.luuppi(5);
 }
