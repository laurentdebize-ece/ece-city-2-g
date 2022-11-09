#include "sims.h"
#include "sims.c"

int main() {
    initAllegro();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT_QUEUE *temps = NULL;
    ALLEGRO_EVENT event;
    //ALLEGRO_BITMAP * map = al_load_bitmap("");
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer = NULL;
    queue = al_create_event_queue();
    display = al_create_display(LARGEURFENETRE, HAUTEURFENETRE);
    timer = al_create_timer(0.1);
    al_set_window_position(display, 0, 0);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_start_timer(timer);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    //al_register_event_source(queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(255, 255, 255));
    ALLEGRO_MOUSE_STATE sourisState;
    //ALLEGRO_KEYBOARD_STATE clavierState;
    short taillePolice = 12;
    ALLEGRO_FONT  * policeTexte = initialiserPoliceTexte(taillePolice);
    ALLEGRO_FONT * policeTexte50 = initialiserPoliceTexte(50);
    ALLEGRO_FONT  * policeTexte2 = initialiserPoliceTexte2(TAILLEPOLICEBOUTTONNORMALE);
    initDonneesJeu();
    bool fin = false;
    al_flip_display();
    do {
        al_wait_for_event(queue, &event);
        //ALLEGRO_KEYBOARD_STATE clavierState;
        //al_get_keyboard_state(&clavierState);
        al_get_mouse_state(&sourisState);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                fin = true;
                break;
            }
            case ALLEGRO_EVENT_TIMER : {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0), policeTexte);
                al_get_mouse_state(&sourisState);
                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
                    al_flip_display();
                }
            }
            al_flip_display();
        }
    }
    while (!fin);
    al_destroy_display(display);
    display = NULL;
    al_destroy_timer(timer);
    al_destroy_event_queue(temps);
    return 0;
}