extends Control

var core: Discord.Core
var users: Discord.UserManager
var images: Discord.ImageManager

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

		images = _get_image_manager()

		var handle: = Discord.ImageHandle.new()
		handle.id = 425340416531890178
		handle.size = 128

		images.fetch(handle, true, self, "fetch_callback")

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

func _get_image_manager() -> Discord.ImageManager:
	var result = core.get_image_manager()
	if result is int:
		print(
			"Failed to get image manager: ",
			enum_to_string(Discord.Result, result)
		)
		return null
	else:
		return result

func _on_current_user_update() -> void:
	users.get_current_user(self, "get_current_user_callback")
	users.get_current_user_premium_type(
		self, "get_current_user_premium_type_callback"
	)

func get_current_user_callback(result: int, user: Discord.User) -> void:
	if result != Discord.Result.OK:
		print(
			"Failed to get user: ",
			enum_to_string(Discord.Result, result)
		)
	else:
		print("Got Current User:")
		print(user.username, "#", user.discriminator, "  ID: ", user.id)

func get_user_callback(result: int, user: Discord.User) -> void:
	if result == Discord.Result.OK:
		print("Fetched User:")
		print(user.username, "#", user.discriminator, "  ID: ", user.id)
	else:
		print("Failed to fetch user: ", enum_to_string(Discord.Result, result))

func get_current_user_premium_type_callback(
	result: int,
	premium_type: int
) -> void:
	if result != Discord.Result.OK:
		print(
			"Failed to get user premium type: ",
			enum_to_string(Discord.Result, result)
		)
	else:
		print("Current User Premium Type:")
		print(enum_to_string(Discord.PremiumType, premium_type))

func fetch_callback(result: int, handle: Discord.ImageHandle) -> void:
	if result != Discord.Result.OK:
		print(
			"Failed to fetch image handle: ",
			enum_to_string(Discord.Result, result)
		)
	else:
		print("Fetched image handle, ", handle.id, ", ", handle.size)
