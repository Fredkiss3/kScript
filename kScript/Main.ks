cmp Hello do
	# This is where the attributes go
	String name = "hello" # Each variable should be initialized
endcmp

# If a program has a "main" function, it is called
func main(String[] args) do
	if args.length gt 0 do
		print("Hello", args[0]) # console arguments
	else do
		print("Hello ", this.name) # Calling "this" refer to the parent component
	endif
endfun
