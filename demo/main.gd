extends Control

var core: Discord.Core

func enum_to_string(the_enum: Dictionary, value: int) -> String:
	var index: = the_enum.values().find(value)
	var string: String = the_enum.keys()[index]
	return string

func _ready() -> void:
	core = Discord.Core.new()
	var result: int = core.create(
		793449535632441374,
		Discord.CreateFlags.DEFAULT
	)
	print("Created Discord Core: ", enum_to_string(Discord.Result, result))
	if result != Discord.Result.OK:
		core = null

func _process(_delta: float) -> void:
	if core:
		var result: int = core.run_callbacks()
		if result != Discord.Result.OK:
			print("Callbacks failed: ", enum_to_string(Discord.Result, result))
