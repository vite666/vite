# -*- coding: utf-8 -*-

'游戏功能实现模块'

__author__='ViTe-志尊威少'

import sys
import pygame
from bullet import Bullet
from alien import Alien
from time import sleep
import json
#事件监控
def check_events(ai_settings,screen,stats,sb,play_button,ship,aliens,bullets):
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit()
        elif event.type==pygame.KEYDOWN:
           check_keydown_events(event,ai_settings,screen,ship,bullets,stats,sb,aliens)
        elif event.type==pygame.KEYUP:
            check_keyup_events(event,ship)
        elif event.type==pygame.MOUSEBUTTONDOWN:
            mouse_x,mouse_y=pygame.mouse.get_pos()
            check_play_button(ai_settings,screen,stats,sb,play_button,ship,aliens,bullets,mouse_x,mouse_y)
def check_keydown_events(event,ai_settings,screen,ship,bullets,stats,sb,aliens):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = True
    elif event.key == pygame.K_LEFT:
        ship.moving_left = True
    elif event.key==pygame.K_SPACE:
        fire_bullet(ai_settings,screen,ship,bullets)
        ai_settings.bullet_sound.play()
    elif event.key==pygame.K_q:
        sys.exit()
    elif event.key==pygame.K_UP:
        ship.moving_up=True
    elif event.key==pygame.K_DOWN:
        ship.moving_dowm=True
    elif event.key==pygame.K_p:
        replay(stats,sb,aliens,bullets,ship,ai_settings,screen)
def check_keyup_events(event,ship):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = False
    elif event.key == pygame.K_LEFT:
        ship.moving_left = False
    elif event.key==pygame.K_UP:
        ship.moving_up=False
    elif event.key==pygame.K_DOWN:
        ship.moving_dowm=False
#屏幕更新
def update_screen(ai_settings,screen,stats,sb,ship,aliens,bullets,play_button):
    screen.fill(ai_settings.bg_color)
    for bullet in bullets.sprites():
        bullet.draw_bullet()
    ship.blitme()
    appear_alien(stats,aliens,screen)
    sb.show_score()
    if not stats.game_active:
        play_button.draw_button()

    #让最近绘制的屏幕可见
    pygame.display.flip()
#子弹相关配置
def update_bullets(ai_settings,screen,stats,sb,ship,aliens,bullets):
    bullets.update()
    for bullet in bullets.copy():
        if bullet.rect.bottom<=0:
            bullets.remove(bullet)
    check_bullet_alien_collisions(ai_settings,screen,stats,sb,ship,aliens,bullets)
def fire_bullet(ai_settings,screen,ship,bullets):
    if len(bullets)< ai_settings.bullets_allowed:
        new_bullet=Bullet(ai_settings,screen,ship)
        bullets.add(new_bullet)


#外星人相关配置
def create_fleet(ai_settings,screen,aliens,stats):
    alien_number=int(stats.level*10)
    for i in range(alien_number):
        alien=Alien(ai_settings,screen)
        aliens.add(alien)
def appear_alien(stats,aliens,screen):
    i=0
    if stats.game_active:
        for e in aliens:
            if i<=5:
                e.move()
                screen.blit(e.image,e.rect)
            i+=1
def update_aliens(ai_settings,stats,screen,sb,ship,aliens,bullets):
    if pygame.sprite.spritecollideany(ship,aliens):
        ship_hit(ai_settings,stats,screen,sb,ship,aliens,bullets)
    check_aliens_bottom(screen,aliens)
def check_aliens_bottom(screen,aliens):
    screen_rect=screen.get_rect()
    for alien in aliens.sprites():
        if alien.rect.bottom>=screen_rect.bottom:
            aliens.remove(alien)

#处理射击事件
def check_bullet_alien_collisions(ai_settings,screen,stats,sb,ship,aliens,bullets):
    collisions=pygame.sprite.groupcollide(bullets,aliens,True,True)
    if collisions:
        for aliens in collisions.values():
            stats.score+=ai_settings.alien_points
            sb.prep_score()
        check_high_score(stats,sb)
    if len(aliens)==0:
        bullets.empty()
        ai_settings.increase_speed()
        stats.level+=1
        sb.prep_level()
        create_fleet(ai_settings,screen,aliens,stats)

#处理撞击事件
def ship_hit(ai_settings,stats,screen,sb,ship,aliens,bullets):
    if stats.ships_left>0:
        ai_settings.I_down_sound.play()
        aliens.empty()
        stats.ships_left-=1
        sb.prep_ships()
        bullets.empty()
        create_fleet(ai_settings,screen,aliens,stats)
        ship.center_ship()
        sleep(0.5)
    else:
        ai_settings.I_down_sound.play()
        stats.game_active=False
        pygame.mouse.set_visible(True)
def check_play_button(ai_settings,screen,stats,sb,play_button,ship,aliens,bullets,mouse_x,mouse_y):
    button_clicked=play_button.rect.collidepoint(mouse_x,mouse_y)
    if button_clicked and not stats.game_active:
        replay(stats,sb,aliens,bullets,ship,ai_settings,screen)
def replay(stats,sb,aliens,bullets,ship,ai_settings,screen):
    stats.reset_stats()
    stats.game_active = True
    sb.prep_score()
    sb.prep_high_score()
    sb.prep_level()
    sb.prep_ships()
    aliens.empty()
    bullets.empty()
    create_fleet(ai_settings, screen,aliens,stats)
    ship.center_ship()
    ai_settings.initialize_dynamic_settings()
    pygame.mouse.set_visible(False)
#检查最高分
def check_high_score(stats,sb):
    if stats.score>stats.high_score:
        stats.high_score=stats.score
        with open('data.txt','w')as f:
            json.dump(stats.score,f)
        sb.prep_high_score()
