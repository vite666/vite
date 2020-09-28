# -*- coding: utf-8 -*-

'得分显示类'

__author__='ViTe-志尊威少'

import pygame.font
from pygame.sprite import Group
from ship import Ship
class Scoreboard():
    def __init__(self,ai_settings,screen,stats):
        self.screen=screen
        self.screen_rect=screen.get_rect()
        self.ai_settings=ai_settings
        self.stats=stats
        self.text_color=(30,30,30)
        self.font=pygame.font.SysFont('simHei',15)
        self.prep_score()
        self.prep_high_score()
        self.prep_level()
        self.prep_ships()
    def show_score(self):
        self.screen.blit(self.score_image,self.score_rect)
        self.screen.blit(self.high_score_image,self.high_score_rect)
        self.screen.blit(self.level_image,self.level_rect)
        self.ships.draw(self.screen)
#显示得分
    def prep_score(self):
        '''将得分转换为图像'''
        rounder_score=int(round(self.stats.score,-1))
        score_str='{:,}'.format(rounder_score)
        self.score_image=self.font.render(str('得分：'+score_str),True,self.text_color,self.ai_settings.bg_color)
        self.score_rect=self.score_image.get_rect()
        self.score_rect.right=self.screen_rect.right-20
        self.score_rect.top=20
#显示历史最高分
    def prep_high_score(self):
        high_score=int(round(self.stats.high_score,-1))
        high_score_str='{:,}'.format(high_score)
        self.high_score_image=self.font.render(str('历史最高分：'+high_score_str),True,self.text_color,self.ai_settings.bg_color)
        self.high_score_rect=self.high_score_image.get_rect()
        self.high_score_rect.centerx=self.screen_rect.centerx
        self.high_score_rect.top=self.score_rect.top
#显示等级
    def prep_level(self):
        self.level_image=self.font.render(str('等级：'+str(self.stats.level)),True,self.text_color,self.ai_settings.bg_color)
        self.level_rect=self.level_image.get_rect()
        self.level_rect.right=self.score_rect.right
        self.level_rect.top=self.score_rect.bottom+10
#显示剩余飞船数
    def prep_ships(self):
        self.ships=Group()
        for ship_number in range(self.stats.ships_left):
            ship = Ship(self.ai_settings,self.screen)
            ship.rect.x=10+ship_number*ship.rect.width
            ship.rect.y=10
            self.ships.add(ship)
