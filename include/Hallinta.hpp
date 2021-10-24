#pragma once
#include <Hallintarajapinta.hpp>
#include <memory>
#include <vector>

class Hallinta {
  std::vector<std::weak_ptr<Hallintarajapinta> > subjektit;
public:
  void lisaaSubjekti(std::weak_ptr<Hallintarajapinta>);
  void piirraKaikki();
  void laskeKaikki();
};
