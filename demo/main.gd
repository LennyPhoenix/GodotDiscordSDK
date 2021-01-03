extends Control

var core: Discord.Core
var users: Discord.UserManager

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
	else:
		users = _get_user_manager()
		users.connect("current_user_update", self, "_on_current_user_update")
		users.get_user(425340416531890178, self, "get_user_callback")

func _process(_delta: float) -> void:
	if core:
		var result: int = core.run_callbacks()
		if result != Discord.Result.OK:
			print("Callbacks failed: ", enum_to_string(Discord.Result, result))

func _get_user_manager() -> Discord.UserManager:
	var result = core.get_user_manager()
	if result is int:
		print(
			"Failed to get user manager: ",
			enum_to_string(Discord.Result, result)
		)
		return null
	else:
		return result

func _on_current_user_update() -> void:
	users.get_current_user(self, "get_current_user_callback")

func get_current_user_callback(result: int, user: Discord.User) -> void:
	if result != Discord.Result.OK:
		print(
			"Failed to get user: ",
			enum_to_string(Discord.Result, result)
		)
	else:
		print("Current User Updated:")
		print(user.username, "#", user.discriminator, "  ID: ", user.id)

func get_user_callback(result: int, user: Discord.User) -> void:
	if result == Discord.Result.OK:
		print("Fetched User:")
		print(user.username, "#", user.discriminator, "  ID: ", user.id)
	else:
		print("Failed to fetch user: ", enum_to_string(Discord.Result, result))
