#include <SFML/Graphics.hpp>
#include <list>
#include "Classes.h"
using namespace std;

int main()
{
	int score = 0;
	RenderWindow window(VideoMode(W, H), "BattleShip", Style::Fullscreen); //создаем окно
	window.setFramerateLimit(60); //это фигня для стабилизации фпс
	
	Texture menuTexture;
	menuTexture.loadFromFile("images/menu.png");
	Sprite menuSprite(menuTexture);	//тестура и спрайт менюшки
	Texture heart_t;
	heart_t.loadFromFile("images/heart.png");
	Sprite heart(heart_t);//то же для сердца (жизни)
	heart.setScale(0.2, 0.2); //размер сердца 
	heart.setPosition(20, 40);
	Texture explosion1_t;	//тут зашружаем текстурки взрывов
	explosion1_t.loadFromFile("images/explosion_1.png");
	Texture explosion2_t;
	explosion2_t.loadFromFile("images/explosion_2.png");
	Texture explosion3_t;
	explosion3_t.loadFromFile("images/explosion_3.png");
	Texture explosion4_t;
	explosion4_t.loadFromFile("images/explosion_4.png");
	Texture explosion5_t;
	explosion5_t.loadFromFile("images/explosion_5.png");
	Texture explosionb_t;
	explosionb_t.loadFromFile("images/explosion_b.png");
	Texture fire_t;
	fire_t.loadFromFile("images/fire.png");
	Texture shield_t;		//текстурка щита
	shield_t.loadFromFile("images/shield.png");
	Animation explosion1_a(explosion1_t, 0, 0, 50, 50, 20, 0.4); //загружаем текстуры взрывов в клас анимации (цифры - это параметры тайлсета)
	Animation explosion2_a(explosion2_t, 0, 0, 120, 120, 16, 0.5);
	Animation explosion3_a(explosion3_t, 0, 0, 140, 140, 48, 0.5);
	Animation explosion4_a(explosion4_t, 0, 0, 175, 200, 16, 0.35);
	Animation explosion5_a(explosion5_t, 0, 0, 140, 150, 11, 0.3);
	Animation explosionb_a(explosionb_t, 0, 0, 120, 120, 64, 0.8);
	Animation fire_a(fire_t, 0, 0, 200, 200, 16, 0.5);
	Animation shield_a(shield_t, 0, 0, 200, 200, 20, 0.3);
	Font font;//шрифт для вывода очков
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Black);
	text.setStyle(Text::Bold);
	
	
	Texture sky_t;//небо и вода (задний фон)
	sky_t.loadFromFile("images/sky.png");
	Sprite sky(sky_t);	
	Texture water_t;
	water_t.loadFromFile("images/water.png");
	Sprite water(water_t);
	water.setPosition(0, 500);
	Texture bullet1_t;//грузим текстуры и анимации пули№1, №2, самолета, торпеды и короБля=)
	bullet1_t.loadFromFile("images/bullet1.png");
	Animation bullet1_a(bullet1_t,0,0, 34, 7, 1, 0);
	Texture bullet2_t;
	bullet2_t.loadFromFile("images/bullet2.png");
	Animation bullet2_a(bullet2_t, 0, 0, 40, 9, 1, 0);
	Texture plane_t;
	plane_t.loadFromFile("images/plane.png");
	Animation plane_a(plane_t, 0, 0, 120, 36, 1, 0);
	Plane plane;
	plane.settings(plane_a, 200,200, 0, 0);
	Texture missile_t;
	missile_t.loadFromFile("images/missile.png");
	Animation missile_a(missile_t, 0, 0, 26, 10, 1, 0);
	Missile* missile = new Missile();
	missile->settings(missile_a, 200 + 60, 200 + 36, 0, 0);
	missile->z_pressed = false;
	Texture barrel_t;//Это ствол пушки на корабле
	barrel_t.loadFromFile("images/barrel.png");
	Animation barrel_a(barrel_t, 0, 0, 104, 16, 1, 0);
	Texture ship_t;
	ship_t.loadFromFile("images/ship2.png");
	Animation ship_a1(ship_t, 0, 0, 650, 200, 1, 0);
	Ship* ship = new Ship();
	ship->settings(ship_a1, 1000, 400, 0, 0);//здесь размещаем стволы в определенные позиции на корабле
	ship->b1->settings(barrel_a, ship->get_position().x + 190, ship->get_position().y + 130, 180 + rand()%180, 0);	 ship->b1->id = (int)ship;
	ship->b2->settings(barrel_a, ship->get_position().x + 245, ship->get_position().y + 120, 180 + rand() % 180, 0); ship->b2->id = (int)ship;
	ship->b3->settings(barrel_a, ship->get_position().x + 291, ship->get_position().y + 106, 180 + rand() % 180, 0); ship->b3->id = (int)ship;
	ship->b4->settings(barrel_a, ship->get_position().x + 447, ship->get_position().y + 109, 180 + rand() % 180, 0); ship->b4->id = (int)ship;
	ship->b5->settings(barrel_a, ship->get_position().x + 490, ship->get_position().y + 125, 180 + rand() % 180, 0); ship->b5->id = (int)ship;
	
	

	std::list<Entity*> entities; //список для всех наших игровых элементов (кроме самолета)
	float x = 300, y = 300;
	int kill_ship = 0; //переменная для анимации взрыва корабля
	entities.push_back(missile);	//запихиваем в стек все, что создали
	entities.push_back(ship);
	entities.push_back(ship->b1);
	entities.push_back(ship->b2);
	entities.push_back(ship->b3);
	entities.push_back(ship->b4);
	entities.push_back(ship->b5);
	float time = 0;
	int life = 0;	//жизни самолета. Считаются от 0 до 3. Патамушта
	bool shielded = false;	//если самолет в щите
	bool game_over = false, stop_game = false, space_pressed = false;
	while (window.isOpen())//до тех пор, пока окно открыто
	{
		time += 0.06; //увеличиваем переменную-счетчик
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)//Если нажали на крестик окна(его нету, посколько полноразмерный экран)
				window.close();
			if(event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space) {//Если пробел - то стреляем (создаем пулю и заносим в список)
					x = plane.get_position().x + 100;
					y = plane.get_position().y + 32;
					Bullet *b = new Bullet("bullet_b");
					b->settings(bullet1_a, x, y, 0, 10);
					entities.push_back(b);
				}
		}
		while (!space_pressed) {//цикл для менюшки
			if (Keyboard::isKeyPressed(Keyboard::Space)) space_pressed = true;
			if (Keyboard::isKeyPressed(Keyboard::Escape)) exit(0);
			window.clear();//очищаем окно
			window.draw(menuSprite);//рисуем спрайт меню
			window.display();//отображаем его в окне
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) exit(0); //Если эскейп - закрываем прогу
		if (!shielded) { //если самолет в щите - его нельзя двигать
			if (Keyboard::isKeyPressed(Keyboard::Left)) plane.keyPressed(Keyboard::Left); //двигаем самолет
			else plane.keyReleased(Keyboard::Left);
			if (Keyboard::isKeyPressed(Keyboard::Right)) plane.keyPressed(Keyboard::Right);
			else plane.keyReleased(Keyboard::Right);
			if (Keyboard::isKeyPressed(Keyboard::Down)) plane.keyPressed(Keyboard::Down);
			else plane.keyReleased(Keyboard::Down);
			if (Keyboard::isKeyPressed(Keyboard::Up)) plane.keyPressed(Keyboard::Up);
			else plane.keyReleased(Keyboard::Up);
		}	
		if (Keyboard::isKeyPressed(Keyboard::Z)) missile->z_pressed = true; //кидаем торпеду (точнее говорим, что ее можно кидать)
		
		plane.update();
		plane.get_animation().update();//обновляем позицию и анимацию самолета
		if (time > 100) {	//создаем новый корабль
			Ship* s = new Ship();
			s->settings(ship_a1, 1366, 400, 0, 0);
			s->b1->settings(barrel_a, s->get_position().x + 190, s->get_position().y + 130, 180 + rand() % 180, 0); s->b1->id = (int)s;
			s->b2->settings(barrel_a, s->get_position().x + 245, s->get_position().y + 120, 180 + rand() % 180, 0); s->b2->id = (int)s;
			s->b3->settings(barrel_a, s->get_position().x + 291, s->get_position().y + 106, 180 + rand() % 180, 0); s->b3->id = (int)s;
			s->b4->settings(barrel_a, s->get_position().x + 447, s->get_position().y + 109, 180 + rand() % 180, 0); s->b4->id = (int)s;
			s->b5->settings(barrel_a, s->get_position().x + 490, s->get_position().y + 125, 180 + rand() % 180, 0); s->b5->id = (int)s;
			entities.push_back(s);
			entities.push_back(s->b1);
			entities.push_back(s->b2);
			entities.push_back(s->b3);
			entities.push_back(s->b4);
			entities.push_back(s->b5);//создали и занесли все элементы в список
			time -= 100;
		}
		if (!missile->z_pressed) {
			missile->set_position(plane.get_position()); //а вот тут уже пускаем торпеду
		}
		for (auto i = entities.begin(); i != entities.end();i++) { //проходим по списку
			Entity*e = *i;
			if (!e->get_name().compare("barrel")) { //если находим в списке пушку, то проверяем ее внутреннюю переменную фаер
				if (e->fire > 500) {
					e->fire -= 500;	//если фаер больше 500 - то стреляем (создаем пулю и заносим в список)
					Bullet *b = new Bullet("bullet_r");
					float x = e->get_animation().get_sprite().getPosition().x+(cos(e->get_angle()*0.017453f) * 40);
					float y = e->get_animation().get_sprite().getPosition().y+(sin(e->get_angle()*0.017453f) * 40);
					b->settings(bullet2_a, x, y, e->get_angle(), 10);
					entities.push_back(b);
				}
			}
		}
		if (plane.get_life() == 0) { //если у самолета 0 жизней (не глобальных, а локальных). Патамушта.
			Explosion *e = new Explosion("explosion"); //создаем взрыв
			e->settings(explosion3_a, plane.get_position().x-10, plane.get_position().y-42, 0, 0);
			e->fire = 2; //это дополнительная переменная для того, чтобы отличить взрыв самолета, от, допустим, взрыва корабля
			entities.push_back(e);
			if (life < 2) { //а тут проверяем глобальные жизни
				plane.settings(plane_a, 200.0f, 200.0f, 0, 0);//ставим самолет в начальную позицию
				plane.set_life(); //обновляем локальную переменную жизни
				Explosion *ex = new Explosion("shield");//щит как щит...
				ex->settings(shield_a, plane.get_position().x - 40, plane.get_position().y - 60, 0, 0);
				entities.push_back(ex);
				shielded = true;
				life++;
			}
			else { //если их нет - заканчиваем игру (убираем самолетик с экрана)
				game_over = true;
				plane.settings(plane_a, -200.0f, -200.0f, 0, 0);
				plane.set_life();
			}
		}
		
		
		for (auto a : entities)//весь этот цикл - проход по всем элементам списка и сравнение его элементов между собой
			for (auto b : entities) {//при встрече определенных элементов проверяется, налаживаются ли они друг на друга
				if (!a->get_name().compare("barrel") && !b->get_name().compare("bullet_b")) {//если да - выполняется определенное действие
					float x = a->get_rect().left + (cos(a->get_angle()*0.017453f) * 60);
					float y = a->get_rect().top + (sin(a->get_angle()*0.017453f) * 60);//тут страшная формула с тригонометрией
					FloatRect r(x, y, a->get_rect().width, a->get_rect().height);
					if (r.intersects(b->get_rect())) {
						a->kill(); b->kill();//убавляем жизни у объектов
						Explosion *e = new Explosion("explosion");
						e->settings(explosion4_a, a->get_position().x, a->get_position().y-109, 0, 0);
						entities.push_back(e);
						score += 20;
					}
				}
				if (!a->get_name().compare("ship") && !b->get_name().compare("bullet_b")) {
					float x = a->get_rect().left;
					float y = a->get_rect().top;
					FloatRect *r = new FloatRect[5];//корабль нельзя описать одним прямоуголтником, поэтому разбиваем на несколько
					r[0] = FloatRect(x, y + 131, 182, 200 - 131);
					r[1] = FloatRect(x+182, y + 120, 232-182, 11);
					r[2] = FloatRect(x+232, y + 108, 50, 23);
					r[3] = FloatRect(x+282, y + 83, 28, 25);
					r[4] = FloatRect(x+310, y, 40, 83);
					for (int i = 0; i < 5; i++) {
						if (r[i].intersects(b->get_rect())) {
							b->kill();
							Explosion *e = new Explosion("explosion");
							e->settings(explosion1_a, b->get_position().x, b->get_position().y, 0, 0);
							entities.push_back(e);
							score += 1;
						}
					}
				}
				if (!a->get_name().compare("bullet_r") && !b->get_name().compare("bullet_b")) {
					if (a->get_rect().intersects(b->get_rect())) {
						a->kill(); b->kill();
						Explosion *e = new Explosion("explosion");
						e->settings(explosion1_a, a->get_position().x, a->get_position().y, 0, 0);
						entities.push_back(e);
						score += 5;
					}
				}
				if (!a->get_name().compare("barrel") && !b->get_name().compare("missile")) {
					float x = a->get_rect().left + (cos(a->get_angle()*0.017453f) * 60);
					float y = a->get_rect().top + (sin(a->get_angle()*0.017453f) * 60);
					FloatRect r(x, y, a->get_rect().width, a->get_rect().height);
					if (r.intersects(b->get_rect())) {
						a->kill(); b->kill();
						Explosion *e = new Explosion("explosion");
						e->settings(explosion4_a, a->get_position().x, a->get_position().y-109, 0, 0);
						entities.push_back(e);
						score += 20;
					}
				}
				if (!a->get_name().compare("ship") && !b->get_name().compare("missile")) {
					float x = a->get_rect().left;
					float y = a->get_rect().top;
					FloatRect *r = new FloatRect[3];
					r[0]= FloatRect(x, y + 131, 282, 200 - 131);
					r[1]= FloatRect(x + 282, y + 66, 454-282, 200-66);
					r[2]= FloatRect(x + 454, y + 131, 650-454, 200-131);
					 	if (r[0].intersects(b->get_rect())&&(a->fire!=1 && a->fire != 4&& a->fire != 6&& a->fire != 9)) {
							Explosion *e = new Explosion("fire");
							e->settings(fire_a, r[0].left, r[0].top-131, 0, 0);
							e->id = (int)a;
							entities.push_back(e);
							e = new Explosion("explosion");
							e->settings(explosion2_a, r[0].left+50, r[0].top - 100, 0, 0); 
							b->kill();
							a->fire += 1;
							entities.push_back(e);
							score += 30;
						}
						if (r[1].intersects(b->get_rect()) && (a->fire != 3 && a->fire != 4 && a->fire != 8 && a->fire != 9)) {
							Explosion *e = new Explosion("fire");
							e->settings(fire_a, r[1].left, r[1].top-100, 0, 0); 
							e->id = (int)a;
							entities.push_back(e);
							e = new Explosion("explosion");
							e->settings(explosion2_a, r[1].left + 50, r[1].top - 60, 0, 0);
							b->kill();
							a->fire += 3;
							entities.push_back(e);
							score += 30;
						}
						if (r[2].intersects(b->get_rect()) && (a->fire != 5 && a->fire != 8 && a->fire != 6 && a->fire != 9)) {
							Explosion *e = new Explosion("fire");
							e->settings(fire_a, r[2].left, r[2].top-131, 0, 0);
							e->id = (int)a;
							entities.push_back(e);
							e = new Explosion("explosion");
							e->settings(explosion2_a, r[2].left + 50, r[2].top - 100, 0, 0);
							b->kill();
							a->fire += 5;
							entities.push_back(e);
							score += 30;
						}
				}
				if (!a->get_name().compare("ship")) {
					float x = a->get_rect().left;
					float y = a->get_rect().top;
					FloatRect *r = new FloatRect[3];
					r[0] = FloatRect(x, y + 131, 282, 200 - 131);
					r[1] = FloatRect(x + 282, y + 66, 454 - 282, 200 - 66);
					r[2] = FloatRect(x + 454, y + 131, 650 - 454, 200 - 131);
					if (r[0].intersects(plane.get_rect()) && (a->fire != 1 && a->fire != 4 && a->fire != 6 && a->fire != 9)) {
						Explosion *e = new Explosion("fire");
						e->settings(fire_a, r[0].left, r[0].top - 131, 0, 0);
						e->id = (int)a;
						entities.push_back(e);
						e = new Explosion("explosion");
						e->settings(explosion2_a, r[0].left + 50, r[0].top - 100, 0, 0);
						plane.kill();
						a->fire += 1;
						entities.push_back(e);
						score += 30;
					}
					if (r[1].intersects(plane.get_rect()) && (a->fire != 3 && a->fire != 4 && a->fire != 8 && a->fire != 9)) {
						Explosion *e = new Explosion("fire");
						e->settings(fire_a, r[1].left, r[1].top - 100, 0, 0);
						e->id = (int)a;
						entities.push_back(e);
						e = new Explosion("explosion");
						e->settings(explosion2_a, r[1].left + 50, r[1].top - 60, 0, 0);
						plane.kill();
						a->fire += 3;
						entities.push_back(e);
						score += 30;
					}
					if (r[2].intersects(plane.get_rect()) && (a->fire != 5 && a->fire != 8 && a->fire != 6 && a->fire != 9)) {
						Explosion *e = new Explosion("fire");
						e->settings(fire_a, r[2].left, r[2].top - 131, 0, 0);
						e->id = (int)a;
						entities.push_back(e);
						e = new Explosion("explosion");
						e->settings(explosion2_a, r[2].left + 50, r[2].top - 100, 0, 0);
						plane.kill();
						a->fire += 5;
						entities.push_back(e);
						score += 30;
					}
				}
				if (!a->get_name().compare("bullet_r") && !b->get_name().compare("missile")) {
					if (a->get_rect().intersects(b->get_rect())) {
						a->kill(); b->kill();
						Explosion *e = new Explosion("explosion");
						e->settings(explosionb_a, b->get_position().x-20, b->get_position().y-60, 0, 0);
						entities.push_back(e);
					}
				}
				if (!a->get_name().compare("bullet_r")) {
					if (a->get_rect().intersects(plane.get_rect())) {
						a->kill(); plane.kill();
					}
				}
				if (!a->get_name().compare("shield") && b->get_name().compare("shield")) {
					if (a->get_rect().intersects(b->get_rect())) {
						b->kill();
					}
				}
			}

		
		for (auto e : entities) {//цикл для проверки, выполнился ли взрыв (щит), его анимация полностью. Если да - убираем его с экрана
			if (!e->get_name().compare("explosion") || !e->get_name().compare("shield")) 
				if (e->get_animation().isEnd()) {
					if (e->fire == 2 && game_over) {
						stop_game = true;
					}
					e->kill();
					if (!e->get_name().compare("shield")) shielded = false;
				}
			if (!e->get_name().compare("ship")) {//весь этот цикл для красивенького взрыва корабля. Когды мы попали во все его три части, 
				if (e->fire == 9) {		
					kill_ship += 5;
					if (kill_ship < 500) {
						if (kill_ship % 40 == 0) {//появляютя рандомно взрывы (каждые 40 тактов)
							float x = e->get_rect().left;
							float y = e->get_rect().top;
							float w = e->get_rect().width;
							float h = e->get_rect().height;
							int i = rand() % 5;
							Explosion *ex;
							switch (i) {
							case 0:
								ex = new Explosion("explosion");
								ex->settings(explosion4_a, x + rand() % (int)w, y + rand() % (int)h, 0, 0);
								entities.push_back(ex);
								break;
							case 1:
								ex = new Explosion("explosion");
								ex->settings(explosion2_a, x + rand() % (int)w, y + rand() % (int)h, 0, 0);
								entities.push_back(ex);
								break;
							case 2:
								ex = new Explosion("explosion");
								ex->settings(explosion3_a, x + rand() % (int)w, y + rand() % (int)h, 0, 0);
								entities.push_back(ex);
								break;
							case 3:
								ex = new Explosion("explosion");
								ex->settings(explosionb_a, x + rand() % (int)w, y + rand() % (int)h, 0, 0);
								entities.push_back(ex);
								break;
							default:
								ex = new Explosion("fire");
								ex->settings(fire_a, x + rand() % (int)w, y + rand() % (int)h, 0, 0);
								entities.push_back(ex);
								ex->id = (int)e;
								break;
							}
						}
						
					}
					else { //как только переменная килл_щип достигает 500 - убираем корабль + насчитываем очки
						for (auto a : entities) {
							if (!a->get_name().compare("fire")||!a->get_name().compare("barrel"))//если остались пушки или огонь, связанные с кораблем - убираем
								if (a->id == int(e))//иначе пушки будут висеть в воздухе. и огонь. тоже.
									a->kill();
						}
						e->kill();
						kill_ship = 0;
						score += 50;
					}
				}
			}
		}
		for (auto i = entities.begin(); i != entities.end();) {//в этом цикле обновляем позиции и анимации всех элементов списка
			Entity*e = *i;
			e->update();
			e->get_animation().update();
			if (e->get_life() == 0) { //если пациент мертв - убираем его из списка и из нашей жизни
				if (!e->get_name().compare("missile")) {//отдельный случай для торпеды - ее надо вернуть на место
					if (e->fire == 1) {
						Explosion *ex = new Explosion("explosion");
						ex->settings(explosion5_a, e->get_position().x-70, e->get_position().y-140, 0, 0);
						entities.push_back(ex);
					}
					missile = new Missile();
					missile->settings(missile_a, -50, -50, 0, 0);
					missile->z_pressed = false;
					delete e;
					*i = missile;
					i++;
				}
				else {
					i = entities.erase(i);
					delete e;
				}
			}
			else i++;
		}

		heart.setTextureRect(IntRect(life*300, 0, 300, 300)); //устаавливаем нужное сердце из тайлсета
		if (!stop_game) {
			window.clear();
			window.draw(sky);
			window.draw(water);
			for (auto i : entities) i->draw(window);
			plane.draw(window);
			text.setString("Score: " + std::to_string(score));
			text.setPosition(20, 20);
			window.draw(text);
			window.draw(heart);
			window.display();
		}
		else {//если проиграли - не отрисовываем самолет и рисуем надпись
			window.clear();
			window.draw(sky);
			window.draw(water);
			for (auto i : entities) i->draw(window);
			plane.draw(window);
			text.setCharacterSize(80);
			text.setString("You loose!\nScore: " + std::to_string(score));
			text.setPosition(500, 250);
			window.draw(text);
			window.display();
		}
	}
 
	return 0;
}
/*В классах, надеюсь, все понятно*/