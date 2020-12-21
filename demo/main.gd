extends Control

var discord: Discord.Core

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
	return discord.create(771366171110932490, 0)
	discord = Discord.Core.new()
