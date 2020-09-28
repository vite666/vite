# -*- coding: utf-8 -*-

'外星人类'

__author__='ViTe-志尊威少'

import pygame
from pygame.sprite import Sprite
from random import randint

class Alien(Sprite):
    def __init__(self,ai_settings,screen):
        #初始化外星人
        super(Alien,self).__init__()
        self.screen=screen
        self.ai_settings=ai_settings
        self.image=pygame.image.load('images/alien.bmp')
        self.rect=self.image.get_rect()
        self.reset()
        self.x=float(self.rect.x)

    def update(self):
        self.x+=(self.ai_settings.alien_speed_factor*self.ai_settings.fleet_direction)
        self.rect.x=self.x
    def check_edges(self):
        screen_rect =self.screen.get_rect()
        if self.rect.right>=screen_rect.right:
            return True
        elif self.rect.left<=0:
            return True

    def move(self):
        if self.rect.top < self.ai_settings.screen_height:
            self.rect.top += self.ai_settings.alien_speed_factor


    def reset(self):
        self.rect.left, self.rect.top = (randint(0, self.ai_settings.screen_width - self.rect.width), randint(-5 * self.rect.height, 0))

