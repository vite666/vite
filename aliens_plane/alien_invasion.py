# -*- coding: utf-8 -*-

'游戏运行主程序'

__author__='ViTe-志尊威少'

import pygame
from settings import Settings
from ship import Ship
import game_functions as gf
from pygame.sprite import Group
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard
def run_game():
    ai_settings =Settings()#导入总设置
    screen = pygame.display.set_mode((ai_settings.screen_width,ai_settings.screen_height))
    pygame.display.set_caption('雷霆战机')#窗口标题
    ship=Ship(ai_settings,screen)#生成飞船
    bullets=Group()#生成子弹组
    aliens=Group()#生成外星组
    stats=GameStats(ai_settings)#生成游戏数据库
    play_button=Button(ai_settings,screen,"开始")#生成按钮组件
    gf.create_fleet(ai_settings, screen, aliens, stats)#创造第一批外星人
    sb=Scoreboard(ai_settings,screen,stats)#生成得分等级展示板
#游戏主循环
    while True:
        gf.check_events(ai_settings,screen,stats,sb,play_button,ship,aliens,bullets)#事件监控
        if stats.game_active:#判断游戏状态
            ship.update()#更新飞船状态
            gf.update_bullets(ai_settings,screen,stats,sb,ship,aliens,bullets)#更新子弹状态
            gf.update_aliens(ai_settings,stats,screen,sb,ship,aliens,bullets)#更新外星人状态
        gf.update_screen(ai_settings,screen,stats,sb,ship,aliens,bullets,play_button)#更新屏幕

run_game()#运行游戏


