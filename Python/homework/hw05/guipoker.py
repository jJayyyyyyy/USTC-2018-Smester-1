# guipoker.py

from graphics import *
from pokerapp import PokerApp
from button import Button
from cdieview import ColorDieView

class GraphicsInterface:

    def __init__(self):
        self.win = GraphWin("Dice Poker", 600, 400)
        self.win.setBackground("green3")
        banner = Text(Point(300,30), "Python  Poker  Parlor")
        banner.setSize(24)
        banner.setFill("yellow2")
        banner.setStyle("bold")
        banner.draw(self.win)

        self.maxScore = 0
        self.maxScoreMsg = Text(Point(300,350), "maxScore: %d" % self.maxScore)
        self.maxScoreMsg.draw(self.win)
        self.msg = Text(Point(300,380), "Welcome to the Dice Table")
        self.msg.setSize(18)
        self.msg.draw(self.win)
        self.createDice(Point(300,100), 75)
        self.buttons = []
        self.addDiceButtons(Point(300,170), 75, 30)
        b = Button(self.win, Point(300, 230), 400, 40, "Roll Dice")
        self.buttons.append(b)
        b = Button(self.win, Point(300, 280), 150, 40, "Score")
        self.buttons.append(b)
        b = Button(self.win, Point(570,375), 40, 30, "Quit")
        self.buttons.append(b)
        self.money = Text(Point(300,325), "$100")
        self.money.setSize(18)
        self.money.draw(self.win)


        winHelp = GraphWin("helper", 600, 200)
        s = "The basic set of rules\n"
        intro = Text(Point(100,30), s)
        intro.draw(winHelp)
        s = "① The player starts with $100.\n"
        intro = Text(Point(120,50), s)
        intro.draw(winHelp)
        s = "② Each round costs $10,subtracted from the player's money at the start. \n"
        intro = Text(Point(225,70), s)
        intro.draw(winHelp)
        s = "③ All five dice are rolled randomly.\n"
        intro = Text(Point(130,90), s)
        intro.draw(winHelp)
        s = "④ The player gets two chances to enhance the hand by rerolling some or all of the dice.\n"
        intro = Text(Point(262,110), s)
        intro.draw(winHelp)
        s = "⑤ At the end of the hand, the player's money is updated.\n"
        intro = Text(Point(185,130), s)
        intro.draw(winHelp)

        # winHelp.getMouse()


    def createDice(self, center, size):
        center.move(-3*size,0)
        self.dice = []
        for i in range(5):
            view = ColorDieView(self.win, center, size)
            self.dice.append(view)
            center.move(1.5*size,0)

    def addDiceButtons(self, center, width, height):
        center.move(-3*width, 0)
        for i in range(1,6):
            label = "Die {0}".format(i)
            b = Button(self.win, center, width, height, label)
            self.buttons.append(b)
            center.move(1.5*width, 0)

    def setMoney(self, amt):
        self.money.setText("${0}".format(amt))

    def showResult(self, msg, score):
        if score > 0:
            text = "{0}! You win ${1}".format(msg, score)
            if score > self.maxScore:
                self.maxScore = score
                self.maxScoreMsg.undraw()
                self.maxScoreMsg = Text(Point(300,350), "maxScore: %d" % self.maxScore)
                self.maxScoreMsg.draw(self.win)
        else:
            text = "You rolled {0}".format(msg)
        self.msg.setText(text)

    def setDice(self, values):
        for i in range(5):
            self.dice[i].setValue(values[i])

    def wantToPlay(self):
        ans = self.choose(["Roll Dice", "Quit"])
        self.msg.setText("")
        return ans == "Roll Dice"

    def close(self):
        self.win.close()

    def chooseDice(self):
        # choices is a list of the indexes of the selected dice
        choices = []                   # No dice chosen yet
        while True: 
            # wait for user to click a valid button
            b = self.choose(["Die 1", "Die 2", "Die 3", "Die 4", "Die 5",
                             "Roll Dice", "Score"])

            if b[0] == "D":            # User clicked a die button
                i = int(b[4]) - 1      # Translate label to die index
                if i in choices:       # Currently selected, unselect it
                    choices.remove(i)
                    self.dice[i].setColor("black")
                else:                  # Currently unselected, select it
                    choices.append(i)
                    self.dice[i].setColor("gray")
            else:                      # User clicked Roll or Score
                for d in self.dice:    # Revert appearance of all dice
                    d.setColor("black")
                if b == "Score":       # Score clicked, ignore choices
                    return []
                elif choices != []:    # Don't accept Roll unless some
                    return choices     #   dice are actually selected

    
    def choose(self, choices):
        buttons = self.buttons

        # activate choice buttons, deactivate others
        for b in buttons:
            if b.getLabel() in choices:
                b.activate()
            else:
                b.deactivate()

        # get mouse clicks until an active button is clicked
        while True:
            p = self.win.getMouse()
            for b in buttons:
                if b.clicked(p):
                    return b.getLabel()  # function exit here.



inter = GraphicsInterface()
app = PokerApp(inter)
app.run()

