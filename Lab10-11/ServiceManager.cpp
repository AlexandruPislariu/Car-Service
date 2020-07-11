#include "ServiceManager.h"
#include <random>

void ServiceManager::srv_adauga_masina(const Masina& m)
{
    cos.push_back(m);
}

void ServiceManager::srv_golire_lista() noexcept
{
    cos.clear();
}

int ServiceManager::srv_numar_masini() const noexcept
{
    return cos.size();
}

void ServiceManager::srv_generare_lista(size_t numar_masini, vector<Masina> all)
{
    std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul de masini

/* Adaug masinile amestecate*/
    while (cos.size() < numar_masini && all.size() > 0) {
        cos.push_back(all.back());
        all.pop_back();
    }
}

const vector<Masina>& ServiceManager::cos_manager()
{
    return cos;
}