extends Node


var core: Discord.Core
var users: Discord.UserManager
var images: Discord.ImageManager
var activities: Discord.ActivityManager


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
		destroy_core()
		return

	core.set_log_hook(Discord.LogLevel.DEBUG, self, "_log_hook")

	users = core.get_user_manager()
	images = core.get_image_manager()
	activities = core.get_activity_manager()


func destroy_core() -> void:
	core = null
	users = null
	images = null
	activities = null


func enum_to_string(the_enum: Dictionary, value: int) -> String:
	var index: = the_enum.values().find(value)
	var string: String = the_enum.keys()[index]
	return string
