/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "context.h"
#include "rule.h"
#include "reuse.h"
#include "dynamicrule.h"
#include "highlightdefinition.h"

using namespace TextEditor;
using namespace Internal;

Context::Context() : m_fallthrough(false), m_dynamic(false)
{}

Context::Context(const Context &context) :
    m_id(context.m_id), m_name(context.m_name), m_lineBeginContext(context.m_lineBeginContext),
    m_lineEndContext(context.m_lineEndContext), m_lineEmptyContext(context.m_lineEmptyContext),
    m_fallthroughContext(context.m_fallthroughContext),
    m_itemData(context.m_itemData), m_fallthrough(context.m_fallthrough),
    m_dynamic(context.m_dynamic), m_instructions(context.m_instructions),
    m_definition(context.m_definition)
{
    // Rules need to be deeply copied because of dynamic contexts.
    foreach (const QSharedPointer<Rule> &rule, context.m_rules)
        m_rules.append(QSharedPointer<Rule>(rule->clone()));
}

const Context &Context::operator=(Context copy)
{
    swap(copy);
    return *this;
}

Context::~Context() = default;

void Context::swap(Context &context)
{
    qSwap(m_id, context.m_id);
    qSwap(m_name, context.m_name);
    qSwap(m_lineBeginContext, context.m_lineBeginContext);
    qSwap(m_lineEndContext, context.m_lineEndContext);
    qSwap(m_lineEmptyContext, context.m_lineEmptyContext);
    qSwap(m_fallthroughContext, context.m_fallthroughContext);
    qSwap(m_itemData, context.m_itemData);
    qSwap(m_fallthrough, context.m_fallthrough);
    qSwap(m_dynamic, context.m_dynamic);
    qSwap(m_rules, context.m_rules);
    qSwap(m_instructions, context.m_instructions);
    qSwap(m_definition, context.m_definition);
}

void Context::configureId(const int unique)
{ m_id.append(QString::number(unique)); }

const QString &Context::id() const
{ return m_id; }

void Context::setName(const QString &name)
{
    m_name = name;
    m_id = name;
}

const QString &Context::name() const
{ return m_name; }

void Context::setLineBeginContext(const QString &context)
{ m_lineBeginContext = context; }

const QString &Context::lineBeginContext() const
{ return m_lineBeginContext; }

void Context::setLineEndContext(const QString &context)
{ m_lineEndContext = context; }

const QString &Context::lineEndContext() const
{ return m_lineEndContext; }

void Context::setLineEmptyContext(const QString &context)
{ m_lineEmptyContext = context; }

const QString &Context::lineEmptyContext() const
{ return m_lineEmptyContext; }

void Context::setFallthroughContext(const QString &context)
{ m_fallthroughContext = context; }

const QString &Context::fallthroughContext() const
{ return m_fallthroughContext; }

void Context::setItemData(const QString &itemData)
{ m_itemData = itemData; }

const QString &Context::itemData() const
{ return m_itemData; }

void Context::setFallthrough(const QString &fallthrough)
{ m_fallthrough = toBool(fallthrough); }

bool Context::isFallthrough() const
{ return m_fallthrough; }

void Context::setDynamic(const QString &dynamic)
{ m_dynamic = toBool(dynamic); }

bool Context::isDynamic() const
{ return m_dynamic; }

void Context::updateDynamicRules(const QStringList &captures) const
{
    Internal::updateDynamicRules(m_rules, captures);
}

void Context::addRule(const QSharedPointer<Rule> &rule)
{ m_rules.append(rule); }

void Context::addRule(const QSharedPointer<Rule> &rule, int index)
{ m_rules.insert(index, rule); }

const QList<QSharedPointer<Rule> > & Context::rules() const
{ return m_rules; }

void Context::addIncludeRulesInstruction(const IncludeRulesInstruction &instruction)
{ m_instructions.append(instruction); }

const QList<IncludeRulesInstruction> &Context::includeRulesInstructions() const
{ return m_instructions; }

void Context::clearIncludeRulesInstructions()
{ m_instructions.clear(); }

void Context::setDefinition(const QSharedPointer<HighlightDefinition> &definition)
{ m_definition = definition; }

const QSharedPointer<HighlightDefinition> &Context::definition() const
{ return m_definition; }
