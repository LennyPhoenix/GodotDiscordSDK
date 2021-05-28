extends ScrollContainer


func _process(_delta: float) -> void:
	if DiscordManager.networking:
		var result: int = DiscordManager.networking.flush()
		if result != Discord.Result.OK:
			print(
				"Failed to flush network: ", DiscordManager.enum_to_string(Discord.Result, result)
			)
