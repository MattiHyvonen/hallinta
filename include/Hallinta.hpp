#pragma once
#include <Hallintarajapinta.hpp>
#include <memory>
#include <vector>
#include <functional>

enum Hallintafunktiot {
  HALLINTAFUNKTIO_PIIRRA,
  HALLINTAFUNKTIO_LASKE
};

class Hallinta {
  std::vector<std::weak_ptr<Hallintarajapinta> > subjektit;
public:
  void lisaaSubjekti(std::weak_ptr<Hallintarajapinta>);
  void piirraKaikki();
  void laskeKaikki();
  void suoritaKaikille(Hallintafunktiot f);
};
