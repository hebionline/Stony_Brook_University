#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 20 22:40:07 2019

@author: bin lu
"""

import numpy as np
import math

from AMS516DataExtracted2 import Stock_Price_Data
from AMS516DataExtracted2 import Weight_Matrix
Input_Data = np.array(Stock_Price_Data)
Stock_Price = Input_Data[:, 1]
Data_After_First_Price_Window = len(Stock_Price) - 11 # Should probably be 10

def xBull_Flag_Pattern_Recognition(vnData, Threshold, Capital_To_Invest):
    Pattern_Recognized = True
    hit_grace_win = False
    hit_time = 0
    Num_Of_Trades = 0

    for i in range(vnData):
        # When 1st grid is non-zero, we start to construct the time window which contains 10 time periods.
        if hit_grace_win:
            hit_time += 1
            if hit_time < 11: # Why should it be 11? to buffer the time window
                continue
            else:
                hit_time = 0
                hit_grace_win = False

        if Pattern_Recognized: # Here, the pattern was recognized so we can begin the analysis.s
            if Stock_Price[i + 1] <= Stock_Price[i]:
                continue

            Pattern_Analysis_Window = Stock_Price[i:i + 11] # Should probably be i + 10
            if Pattern_Analysis_Window[0] != np.amin(Pattern_Analysis_Window):
                continue
            Price_Range_Of_Analysis_Window = np.amax(Pattern_Analysis_Window) - np.amin(Pattern_Analysis_Window)
            Grid_Size = Price_Range_Of_Analysis_Window / 10
            Fitting_Value = 5 # Initializing the fitting value
            Current_Row, Current_Column = 9, 0
            Grid_Index_Num = 0

            # The price is mapped to the weight matrix using the Pattern_Analysis_Window, where Pattern_Analysis_Window[0] is the starting point with index[9,0]
            for j in range(9):
                Moving_Length = Pattern_Analysis_Window[j + 2] - Pattern_Analysis_Window[0]
                Grid_Index_Num = math.ceil(Moving_Length / Grid_Size)

                if Grid_Index_Num < 0:
                    break
                elif Grid_Index_Num < 10:
                    Current_Row = 9 - Grid_Index_Num
                else:
                    Current_Row = 0
                Current_Column += 1
                Fitting_Value += Weight_Matrix[Current_Row, Current_Column]
                if Fitting_Value < Threshold:
                    break

            # After the analysis of the price window, we know whether or not it is a bull flag pattern
            if Fitting_Value < Threshold: # Why is it breaking above (3 lines) but not here.
                continue
            else:
                Pattern_Recognized = False
                hit_grace_win += True
                Price_To_Buy = Stock_Price[i + 10]
                Num_Of_Shares = math.floor(Capital_To_Invest / Price_To_Buy)
                Num_Of_Trades += 1
                print("Price when buying the stock =", Price_To_Buy)
                print("Time when buying the stock =", i)

            print("The price range for the analysis window is " + str(Price_Range_Of_Analysis_Window))

            TP_Level = Price_To_Buy + 1.0 * Price_Range_Of_Analysis_Window
            SL_Level = Price_To_Buy - 0.2 * Price_Range_Of_Analysis_Window # Paper used 0.5 for the Stop Loss Level.

        # Trading system is implemented below. Pattern recognization was disabled.
        else: 
            if Stock_Price[i] > TP_Level: # Since we don't have the price instantaneously, we can say that.
                # We can sell the stock at the TP level and take the profit.
                Capital_To_Invest += (TP_Level - Price_To_Buy) * Num_Of_Shares # This probably does not work properly. Should it also be Stock_Price[i] instead of TP_Level
                Pattern_Recognized = True
                print("Stock Price when TP Level is reached =", str(TP_Level))
                print("Take Profit Level = " + str(TP_Level))
                print("The profit on that trade was " + str((TP_Level - Price_To_Buy) * Num_Of_Shares))
                print()

            elif Stock_Price[i] < SL_Level: # Since we don't have the price instantaneously, we can say that.
                # We can sell the stock at the SL level to control the size of the loss.
                Capital_To_Invest += (SL_Level - Price_To_Buy) * Num_Of_Shares # This probably does not work properly. Should it also be Stock_Price[i] instead of SL_Level
                Pattern_Recognized = True
                print("Stock Price when SL Level is reached =", str(SL_Level))
                print("Stop Loss Level = " + str(SL_Level))
                print("The loss on that trade was " + str((Price_To_Buy - TP_Level) * Num_Of_Shares))
                print()
            else:
                # We just hold the stock until a bull pattern is recognized and we are in one of the two cases above. 
                continue

    print("The number of trades made is " + str(Num_Of_Trades))
    print()
    print("The capital to invest after trading is " + str(Capital_To_Invest))
    print()