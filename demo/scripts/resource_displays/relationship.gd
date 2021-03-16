extends PanelContainer


onready var type_line_edit: = $VBoxContainer/Type/LineEdit
onready var user_info: = $VBoxContainer/User
onready var presence_info: = $VBoxContainer/Presence

var relationship: Discord.Relationship setget set_relationship


func set_relationship(new_relationship: Discord.Relationship) -> void:
	if new_relationship:
		type_line_edit.text = DiscordManager.enum_to_string(
			Discord.RelationshipType,
			new_relationship.type
		)
		user_info.user = new_relationship.user
		presence_info.presence = new_relationship.presence
