//Inclusão de bibliotecas padrão
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

int teste(int FPS,int ALTURA,int LARGURA){
    //Inicialização das variáveis com Allegro
    ALLEGRO_DISPLAY * janela = NULL;
    ALLEGRO_EVENT_QUEUE * fila_eventos = NULL;
    ALLEGRO_BITMAP * play = NULL;
    ALLEGRO_BITMAP * play_sel= NULL;
    ALLEGRO_BITMAP * fundo = NULL;
    ALLEGRO_BITMAP * icone = NULL;
    ALLEGRO_FONT * fonte = NULL;
    ALLEGRO_AUDIO_STREAM * voz1 = NULL;
    ALLEGRO_AUDIO_STREAM * voz2 = NULL;


    //Declaração de variáveis
    bool aberto = true;
    bool sel1 = false,
         sel2 = false;
    double tempo_ini = 0,
           tempo_fin = 0;

    //Inicialização das bibliotecas
    al_init();
    al_install_mouse();
    al_init_image_addon();
    al_install_audio(); //Instalação do audio
    al_install_keyboard();
    al_init_font_addon(); //Instalação das fontes
    al_init_ttf_addon();

    //Criação do display e seus elementos gráficos
    janela = al_create_display(LARGURA, ALTURA);
    fila_eventos = al_create_event_queue(); //Criação da fila de eventos
    play = al_load_bitmap("Arte/barrinha.png");
    play_sel = al_load_bitmap("Arte/barrinha_sel.png");
    fundo = al_load_bitmap("Arte/Plano-de-fundo.png");
    icone = al_load_bitmap("Arte/icone.png");
    fonte = al_load_ttf_font("Arte/Arial.ttf", 30, 0);
    voz1 = al_load_sample("Narrador/portugues.ogg");
    voz2 = al_load_sample("Narrador/ingles.ogg");
    //Adição do eventos na fila
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    al_set_display_icon(janela, icone);

    //Primeiro desenho da página
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(play, LARGURA * 0.2, ALTURA * 0.4, 0);
    al_draw_bitmap(play, LARGURA * 0.6, ALTURA * 0.4, 0);


    //Escrevendo a opção no Menu;
    al_draw_textf(fonte, al_map_rgb(255, 255,255), LARGURA * 0.21, ALTURA * 0.41, 0, "Escreva");
    al_draw_textf(fonte, al_map_rgb(255, 255,255), LARGURA * 0.61, ALTURA * 0.41, 0, "Selecione");


    al_flip_display();

    //Título da Janela
    al_set_window_title(janela, "Jogo das Palavras");

    while(aberto){  //Repetição para o display permanecer aberto
        tempo_ini = al_get_time();

        while(!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;

            al_wait_for_event(fila_eventos, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                fechaJanela(janela);
            }else if(evento.type == ALLEGRO_EVENT_KEY_UP){ //Trocas de página de acordo com a tecla pressionada
                switch(evento.keyboard.keycode){
                    case ALLEGRO_KEY_3:
                        main();
                    break;
                    case ALLEGRO_KEY_4:
                        personagens(FPS, ALTURA, LARGURA);
                    break;
                    case ALLEGRO_KEY_5:
                        personagens(FPS, ALTURA, LARGURA);
                    break;
                    case ALLEGRO_KEY_ESCAPE:
                        fechaJanela(janela);
                    break;
                }
            }else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                if(evento.mouse.y > ALTURA* 0.4 && evento.mouse.y < ALTURA * 0.4 + al_get_bitmap_height(play)){
                    if(evento.mouse.x > LARGURA * 0.2 && evento.mouse.x < LARGURA * 0.2 + al_get_bitmap_width(play)){
                        sel1 = true;
                    }else{
                        sel1 = false;
                    }
                    if(evento.mouse.x > LARGURA * 0.6 && evento.mouse.x < LARGURA * 0.6 + al_get_bitmap_width(play)){
                        sel2 = true;
                    }else{
                        sel2 = false;
                    }
                }else{
                    sel1 = false;
                    sel2 = false;
                }

                if(sel1){
                    al_draw_bitmap(play_sel, LARGURA * 0.2, ALTURA * 0.4, 0);
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA * 0.21, ALTURA * 0.41, 0, "Escreva");//Escrevendo a opção no Menu;
                    al_play_sample(voz1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                }
                else{
                    al_draw_bitmap(play, LARGURA * 0.2, ALTURA * 0.4, 0);
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA * 0.21, ALTURA * 0.41, 0, "Escreva");//Escrevendo a opção no Menu;
                }
                if(sel2){
                    al_draw_bitmap(play_sel, LARGURA * 0.6, ALTURA * 0.4, 0);
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA * 0.61, ALTURA * 0.41, 0, "Selecione");//Escrevendo a opção no Menu;
                    al_play_sample(voz2,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                }else{
                    al_draw_bitmap(play, LARGURA * 0.6, ALTURA * 0.4, 0);
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA * 0.61, ALTURA * 0.41, 0, "Selecione");//Escrevendo a opção no Menu;
                }
            }else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                //Alterando as páginas com clique
                if(evento.mouse.x >= LARGURA * 0.6 && evento.mouse.x <= LARGURA * 0.6 + al_get_bitmap_width(play) &&
                    evento.mouse.y >= ALTURA * 0.4 && evento.mouse.y <= ALTURA * 0.4 + al_get_bitmap_height(play)){
                    al_destroy_display(janela);
                    personagens(FPS, LARGURA, ALTURA);
                }
                if(evento.mouse.x >= LARGURA * 0.2 && evento.mouse.x <= LARGURA * 0.2 + al_get_bitmap_width(play) &&
                    evento.mouse.y >= ALTURA * 0.4 && evento.mouse.y <= ALTURA * 0.4 + al_get_bitmap_height(play)){
                    al_destroy_display(janela);
                    personagens(FPS, LARGURA, ALTURA);
                }
            }
        }
        al_flip_display();
    }

    tempo_fin = al_get_time() - tempo_ini;

    if(tempo_fin < 1.0 / FPS){
        al_rest((1.0 / FPS) - (al_get_time()- tempo_ini));
    }

    destruir_fases(janela, fundo, fila_eventos, play, play_sel);

    return 0;
}
