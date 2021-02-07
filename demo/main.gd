extends Control


onready var texture_rect: = $TextureRect

var core: Discord.Core
var users: Discord.UserManager
var images: Discord.ImageManager
var activities: Discord.ActivityManager


func enum_to_string(the_enum: Dictionary, value: int) -> String:
	var index: = the_enum.values().find(value)
	var string: String = the_enum.keys()[index]
	return string


func _ready() -> void:
	core = Discord.Core.new()
	var result: int = core.create(
		807697044516372541,
		Discord.CreateFlags.DEFAULT
	)
	print("Created Discord Core: ", enum_to_string(Discord.Result, result))
	if result != Discord.Result.OK:
		core = null
	else:
		core.set_log_hook(Discord.LogLevel.DEBUG, self, "log_hook")

		users = _get_user_manager()
		images = _get_image_manager()
		activities = _get_activity_manager()

		users.connect("current_user_update", self, "_on_current_user_update")

		users.get_user(425340416531890178, self, "get_user_callback")

		var activity: = Discord.Activity.new()

		activity.details = "Hello from the GodotDiscordSDK!"
		activity.state = "Testing..."

		activity.assets.large_image = "blurpgodot"
		activity.assets.large_text = "Godot Discord Game SDK"
		activity.assets.small_image = "blurpgodot"
		activity.assets.small_text = "Mini Godot"

		activity.timestamps.start = OS.get_unix_time()

		activities.update_activity(activity, self, "update_activity_callback")

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


func _get_activity_manager() -> Discord.ActivityManager:
	var result = core.get_activity_manager()
	if result is int:
		print(
			"Failed to get activity manager: ",
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


func log_hook(level: int, message: String) -> void:
	print(
		"[Discord SDK] ",
		enum_to_string(Discord.LogLevel, level),
		": ", message
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

		var handle: = Discord.ImageHandle.new()
		handle.id = user.id
		handle.size = 256
		handle.type = Discord.ImageType.USER

		images.fetch(handle, true, self, "fetch_callback")


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

		var res = images.get_data(handle)
		if res is int:
			print(
				"Failed to get image data: ",
				enum_to_string(Discord.Result, res)
			)
		else:
			var dimensions: Discord.ImageDimensions = images.get_dimensions(handle)
			var image: = Image.new()
			image.create_from_data(
				dimensions.width, dimensions.height,
				false,
				Image.FORMAT_RGBA8,
				res
			)
			image.unlock()
			var tex: = ImageTexture.new()
			tex.create_from_image(image)
			texture_rect.texture = tex
			OS.window_size = Vector2(dimensions.width, dimensions.height)


func update_activity_callback(result: int):
	if result == Discord.Result.OK:
		print("Updated Activity Successfully")
	else:
		print(
			"Failed to update activity: ",
			enum_to_string(Discord.Result, result)
		)
