extends PanelContainer


onready var relationship_info: = $VBoxContainer/MarginContainer/VBoxContainer/Relationship


func _ready() -> void:
	var _err: = DiscordManager.connect(
		"initialised",
		self, "_on_discord_manager_initialised"
	)


func _on_discord_manager_initialised() -> void:
	DiscordManager.relationships.connect(
		"relationship_update",
		self, "_on_relationship_update"
	)


func _on_relationship_update(relationship: Discord.Relationship) -> void:
	relationship_info.relationship = relationship
