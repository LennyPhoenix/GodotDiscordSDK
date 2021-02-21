extends Node


var core: Discord.Core


func _ready() -> void:
	create_core()


func _process(_delta: float) -> void:
	if core:
		var result: int = core.run_callbacks()
		if result != Discord.Result.OK:
			print(
				"Failed to run callbacks: ",
				enum_to_string(Discord.Result, result)
			)
			destroy_core()


func _log_hook(level: int, message: String) -> void:
	print(
		"[DISCORD] ", enum_to_string(Discord.LogLevel, level),
		": ", message
	)


func create_core() -> void:
	destroy_core()
	core = Discord.Core.new()
	var result: int = core.create(
		807697044516372541,
		Discord.CreateFlags.DEFAULT
	)

	if result != Discord.Result.OK:
		print(
			"Failed to initialise Discord Core: ",
			enum_to_string(Discord.Result, result)
		)
		core = null
		return

	core.set_log_hook(Discord.LogLevel.DEBUG, self, "_log_hook")


func destroy_core() -> void:
	core = null


func enum_to_string(the_enum: Dictionary, value: int) -> String:
	var index: = the_enum.values().find(value)
	var string: String = the_enum.keys()[index]
	return string
