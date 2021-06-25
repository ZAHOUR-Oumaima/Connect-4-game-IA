#ifndef JOUEURVSMACHINE_H_INCLUDED
#define JOUEURVSMACHINE_H_INCLUDED

extern int nbr;
extern int count;

extern int HEURISTIQUE[6][7];
extern int Plateau[6][7];   // plateau du Jeu


void partieMachine(int choixIA);
void JouerVsIA(int choixIA);

#endif // JOUEURVSMACHINE_H_INCLUDED
