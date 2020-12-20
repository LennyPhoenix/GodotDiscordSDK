extends Control

var discord: DiscordCore

func _ready() -> void:
	var result: = reload_discord()
	if result != Discord.Result.OK:
		print(result)

func _process(_delta: float) -> void:
	var result: int = discord.run_callbacks()
	print(result)
	if result != Discord.Result.OK:
		result = reload_discord()

func reload_discord() -> int:
	discord = DiscordCore.new()
	return discord.create(771366171110932490, 0)
