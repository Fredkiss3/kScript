component Enemy :
	Int life = 100
endcomponent

fun update(Float ts) do
	print("This frame took : ", ks, " seconds to render")
endfun

# Each function is a 'Method'
func attack(Int power) do
	this.life -= power 
endfun