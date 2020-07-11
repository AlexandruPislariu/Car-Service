#include "Valid.h"
#include "Exceptii.h"

int validare_masina(Masina m)
{/* Verifica ca datele introduse sa nu fie vide */
	if (m.getNrInmatriculare().size() == 0)
		throw ValidException("Numar inmatriculare invalid\n");
	if (m.getProducator().size() == 0)
		throw ValidException("Producator invalid\n");
	if (m.getModel().size() == 0)
		throw ValidException("Model invalid\n");
	if (m.getTip().size() == 0)
		throw ValidException("Tip invalid\n");

	return 1;
}