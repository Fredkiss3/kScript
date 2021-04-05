


# variable
int v = 5

# type deduction
int myvar = 5

# console
print(i)


# struct Person :
#	string name = "hello"
#	int age = "age"
# endstruct



# function 
# Syntax : 
#		fun <function_name>(<parameter_type> <argument_name>) : <return_type>
#			code ...
#		endfun
#		

fun square(int n) : int 
	return n * n;
endfun

# string
string str = "abc"

# calling method
str.startswith("a")

# Event
# when EventName e do
#	print(e)
# endwhen

# condition
if v == i do
	# loop
	for i in [1, 2, 3] do
		print(i)
	endfor
endif


# Examples of Usage

# 1 - Basic Movement 
Int SPEED = 10
Vector dir = (0, 0)

fun setUp() do
	Input.setLeftButton("Q")
	Input.setRightButton("D")
	Input.setUpButton("Z")
	Input.setDownButton("S")
endfun

fun update(Float ts) do
	dir = Input.getDir() # Input is an object registered in stdlib

	rigidBody.position += Vector(dir.x * SPEED, dir.y * SPEED)
endfun


# Score point

# On a file named Player.ks
component Player :
	String name = ""
	Int score = 0
	Int life = 100

	Enemy enemy = null
	Sword sword = null
endcomponent

fun start(Event e) do
	# Called on the each frame
	this.sword = this.getComponent(Sword)
endfun


fun update(float ts) do
	# Called each frame
endfun

# Called on collision
fun onCollision(Collider other, Bool exit) do
	if !exit do
		this.enemy = other.getComponent(Enemy)
		if enemy != null do 
			this.enemy.attack(this.sword.attackPower)
		endif
	endif
endfun

# on a file named Sword.ks
component Sword :
	Int attackPower = 100
endcomponent


# on a file named Enemy.ks
component Enemy :
	Int life = 100
endcomponent


# KSCRIPT est un langage impératif et chaque fichier est un composant
# Chaque fichier doit commencer par "component"
# Les types doivent toujours commencer par une Majuscule
# Toutes 

