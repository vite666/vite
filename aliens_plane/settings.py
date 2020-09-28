# -*- coding: utf-8 -*-

'游戏总设置'

__author__='ViTe-志尊威少'

import pygame
class Settings():
    def __init__(self):

        #初始化屏幕
        self.screen_width=1100
        self.screen_height=650
        self.bg_color=(230,230,230)

        #飞船相关配置
        self.ship_speed_factor=1
        self.ship_limit=3

        #子弹相关配置
        self.bullet_speed_factor=1
        self.bullet_width=3
        self.bullet_height=15
        self.bullet_color=60,60,60
        self.bullets_allowed=5

        #外星人相关配置
        self.alien_speed_factor =1  #下落速度

        self.speedup_scale=1.1
        self.score_scale=1.5
        self.alien_points=50

        self.initialize_dynamic_settings()



        pygame.init()  # 游戏初始化
        pygame.mixer.init()  # 混音器初始化

        # 游戏背景音乐
        pygame.mixer.music.load("sound/intro.mp3")
        pygame.mixer.music.set_volume(0.2)
        pygame.mixer.music.play(loops=-1)

        # 子弹发射音乐
        self.bullet_sound = pygame.mixer.Sound("sound/biu.wav")
        self.bullet_sound.set_volume(0.2)

        # 我方飞机挂了的音乐
        self.I_down_sound = pygame.mixer.Sound("sound/boom.wav")
        self.I_down_sound.set_volume(0.2)


    def initialize_dynamic_settings(self):
        self.ship_speed_factor=1
        self.bullet_speed_factor=1
        self.alien_speed_factor=1
        self.alien_points=50

    def increase_speed(self):
        self.ship_speed_factor*=self.speedup_scale
        self.bullet_speed_factor*=self.speedup_scale
        self.alien_speed_factor*=self.speedup_scale
        self.alien_points=int(self.alien_points*self.score_scale)